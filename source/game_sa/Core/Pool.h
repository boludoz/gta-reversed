/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <Base.h>
#include <cstdint>

#define INVALID_POOL_SLOT (-1)

/*
    R* terminology      Our terminology
    JustIndex           Index
    Index               Id
    Ref                 Handle/Ref
    Size                Capacity
*/

template<class T, class S = T>
class CPool {
    using ReturnType  = T;               //!< Common base of all these objects, this is the value returned from/expected to all functions
    using StorageType = byte[sizeof(S)]; //!< Memory for the widest object

private:
    struct SlotState {
        uint8 Ref : 7 { 0 };        //!< Incremented each time an object is allocated in this slot (Mask: 0x7F)
        bool  IsEmpty : 1 { true }; //!< If this slot is allocated right now (Mask: 0x80)

        auto ToInt() const { return std::bit_cast<uint8>(*this); }
    };

    VALIDATE_SIZE(SlotState, 1);

private:
    /*
    * Debug fill bytes for compatibility with MSVC/C++ debug heap
    * See
    * \Program Files\Microsoft Visual Studio\VC98\CRT\SRC\DBGHEAP.C:
    * static unsigned char _bNoMansLandFill = 0xFD;
    *   // fill no-man's land with this
    * static unsigned char _bDeadLandFill   = 0xDD;
    *   // fill free objects with this
    * static unsigned char _bCleanLandFill  = 0xCD;
    *   // fill new objects with this
    */
    constexpr static auto NOMANSLAND_FILL = 0xFD; //!< Initial fill of the pool's storage (That is, no objects have ever used this space)
    constexpr static auto DEADLAND_FILL   = 0xDD; //!< Delete'd objects are filled with this
    constexpr static auto CLEANLAND_FILL  = 0xCD; //!< New'd objects are filled with this (Expect the constructor to overwrite most of this)

public:
    /*!
    * @brief Default constructor, with no memory allocated
    */
    CPool() = default;

    /*!
    * @brief Initializes pool, owning memory
    ****/
    CPool(size_t capacity, const char* name) :
        m_Storage{ new StorageType[capacity] },
        m_SlotState{ new SlotState[capacity] },
        m_Capacity{ capacity },
        m_OwnsAllocations{ true }
    {
        assert(m_Storage);
        assert(m_SlotState);

        rng::uninitialized_fill(m_SlotState, m_SlotState + capacity, SlotState{});
        DoFill(NOMANSLAND_FILL);
    }

    /*!
    * @brief Initialises a pool with pre-allocated memory (non-owning)
    * @brief To be called one-time-only for statically allocated pools.
    ****/
    CPool(size_t capacity, void* storage, void* states) :
        m_Storage{ static_cast<StorageType*>(storage) },
        m_SlotState{ static_cast<SlotState*>(states) },
        m_Capacity{ capacity },
        m_OwnsAllocations{ false }
    {
        assert(m_Storage);
        assert(m_SlotState);

        rng::uninitialized_fill(m_SlotState, m_SlotState + capacity, SlotState{});
        DoFill(NOMANSLAND_FILL);
    }

    ~CPool() {
        Flush();
    }

    inline friend void swap(CPool<T, S>& a, CPool<T, S>& b) {
        using std::swap;
    
        swap(a.m_Storage, b.m_Storage);
        swap(a.m_SlotState, b.m_SlotState);
        swap(a.m_Capacity, b.m_Capacity);
        swap(a.m_FirstFreeSlot, b.m_FirstFreeSlot);
        swap(a.m_OwnsAllocations, b.m_OwnsAllocations);
        swap(a.m_DealWithNoMemory, b.m_DealWithNoMemory);
    }

    /* The `Init` function has been replaced by a constructor taking the same args */

    /*!
    * @brief Shut down pool, deallocate
    */
    void Flush() {
        DoFill(NOMANSLAND_FILL);
        if (m_OwnsAllocations) {
            delete[] std::exchange(m_Storage, nullptr);
            delete[] std::exchange(m_SlotState, nullptr);
        }
        m_Capacity         = 0;
        m_LastFreeSlot     = -1;
        m_OwnsAllocations  = false;
        m_DealWithNoMemory = false;
    }

    // Clears pool
    void Clear() {
        for (auto i = 0; i < m_Capacity; i++) {
            m_SlotState[i].IsEmpty = true;
        }
        DoFill(DEADLAND_FILL);
    }

    auto GetSize() {
        return m_Capacity;
    }

    /*!
    * @brief Returns if specified slot is free
    */
    // 0x404940
    bool IsFreeSlotAtIndex(size_t idx) const {
        assert(IsIndexInBounds(idx));
        return m_SlotState[idx].IsEmpty;
    }

    /*!
    * @brief Returns slot index for this object
    */
    auto GetIndex(const T* obj) const {
        assert(IsPtrFromPool(obj));
        return (StorageType*)(obj) - (StorageType*)(m_Storage);
    }

    /*!
    * @brief Returns pointer to object by slot index
    */
    T* GetAt(size_t idx) {
        assert(IsIndexInBounds(idx));
        return !IsFreeSlotAtIndex(idx) ? (T*)&m_Storage[idx] : nullptr;
    }

    /*!
    * @brief Marks slot as free / used (0x404970)
    */
    void SetFreeAt(size_t idx, bool isFree) {
        assert(IsIndexInBounds(idx));
        m_SlotState[idx].IsEmpty = isFree;
    }

    /*!
    * @brief Set new id for slot (0x54F9F0)
    */
    void SetIdAt(size_t idx, uint8 id) {
        assert(IsIndexInBounds(idx));
        m_SlotState[idx].Ref = id;
    }

    /*!
    * @brief Get id for slot (0x552200)
    */
    uint8 GetIdAt(size_t idx) {
        assert(IsIndexInBounds(idx));
        return m_SlotState[idx].Ref;
    }

    /*!
    * @brief Allocates object
    */
    T* New() {
        const auto i = m_LastFreeSlot = FindFreeSlot();
        if (i == -1) {
            if (CanDealWithNoMemory()) {
                NOTSA_LOG_ERR("Allocation failed for type {:?}", typeid(T).name());
            } else {
                NOTSA_DEBUG_BREAK();
            }
            return nullptr;
        }
        assert(IsIndexInBounds(i) && "Free slot index is out-of-bounds");
        assert(IsFreeSlotAtIndex(i) && "Can't allocate an object at a non-free slot");

        auto* const state = &m_SlotState[i];
        const auto isFirstAllocation = state->Ref == 0; // First allocation of this slot?
        state->IsEmpty = false;
        state->Ref++;

        StorageType* ptr = &m_Storage[i];
        // NOTE/TODO: Works, and does find bugs (...that I'm lazy to fix right now)
        //if (!isFirstAllocation) {
        //    CheckFill(DEADLAND_FILL, ptr); // Theoretically `isFirstAllocation ? NOMANSLAND_FILL : DEADLAND_FILL` would work, but we don't have every and all constructor of this class hooked
        //}
        DoFill(CLEANLAND_FILL, ptr);
        return (T*)(void*)(ptr);
    }

    /*!
    * @brief Allocates object at a specific index from a SCM handle (ref) (0x59F610)
    */
    void CreateAtRef(int32 ref) {
        const auto idx           = GetIndexFromRef(ref); // GetIndexFromRef asserts if idx out of range
        assert(IsFreeSlotAtIndex(idx) && "Can't create an object at a non-free slot");

        m_SlotState[idx].IsEmpty = false;
        m_SlotState[idx].Ref     = ref & 0x7F;
        m_LastFreeSlot           = 0;
        while (!m_SlotState[m_LastFreeSlot].IsEmpty) { // Find next free
            ++m_LastFreeSlot;
        }
    }

    /*!
    * @brief Allocate object at ref (0x5A1C00)
    * @returns A ptr to the object at ref
    */
    T* NewAt(int32 ref) {
        const auto idx = GetIndexFromRef(ref);
        assert(IsFreeSlotAtIndex(idx) && "Can't create an object at a non-free slot");

        StorageType* ptr = &m_Storage[idx];
        CreateAtRef(ref);
        DoFill(CLEANLAND_FILL, ptr);
        return (T*)(void*)(ptr);
    }

    /*!
    * @brief Deallocates object
    */
    void Delete(T* obj) {
#ifdef FIX_BUGS // C++ says that `delete nullptr` is well defined, and should do nothing.
        if (!obj) {
            return;
        }
#endif
        assert(!IsFreeSlotAtIndex(GetIndex(obj)) && "Can't delete an already deleted object");

        const auto idx = GetIndex(obj);
        m_SlotState[idx].IsEmpty = true;
        m_LastFreeSlot          = std::min(m_LastFreeSlot, idx);
        DoFill(DEADLAND_FILL, (StorageType*)(obj));
    }

    /*!
    * @brief Returns SCM handle (ref) for object (0x424160)
    */
    int32 GetRef(const T* obj) {
        const auto idx = GetIndex(obj);
        return (idx << 8) | m_SlotState[idx].ToInt();
    }

    /*!
    * @brief Returns pointer to object by SCM handle (ref)
    */
    T* GetAtRef(int32 ref) {
        int32 idx = ref >> 8; // It is possible the ref is invalid here, thats why we check for the idx is valid below (And also why GetIndexFromRef isn't used, it would assert)
        return IsIndexInBounds(idx) && m_SlotState[idx].ToInt() == (ref & 0xFF)
            ? reinterpret_cast<T*>(&m_Storage[idx])
            : nullptr;
    }

    T* GetAtRefNoChecks(int32 ref) {
        return GetAt(GetIndexFromRef(ref));
    }

    /*!
    * @addr 0x54F6B0
    * @brief Calculate the number of used slots. CAUTION: Slow, especially for large pools.
    */
    size_t GetNoOfUsedSpaces() {
        return (size_t)std::count_if(m_SlotState, m_SlotState + m_Capacity, [](auto&& v) {
            return !v.IsEmpty;
        });
    }

    auto GetNoOfFreeSpaces() {
        return m_Capacity - GetNoOfUsedSpaces();
    }

    // 0x54F690
    auto GetObjectSize() {
        return sizeof(S);
    }

    // 0x5A1CD0
    bool IsObjectValid(const T* obj) const {
        return IsPtrFromPool(obj) && !IsFreeSlotAtIndex(GetIndex(obj));
    }

    /*!
    * @brief Check if index is in array bounds
    */
    [[nodiscard]] bool IsIndexInBounds(size_t idx) const {
        return idx >= 0 && idx < m_Capacity;
    }

    /*!
    * @brief Check if the pointer is from this pool 
    */
    bool IsPtrFromPool(const T* ptr) const {
        return m_Storage <= (StorageType*)(ptr) && (StorageType*)(ptr) < m_Storage + m_Capacity;
    }

    /*!
    * @brief Get slot index from ref
    */
    int32 GetIndexFromRef(int32 ref) {
        const auto idx = ref >> 8;
        assert(IsIndexInBounds(idx));
        return idx;
    }

    // notsa
    void SetDealWithNoMemory(bool enabled) { m_DealWithNoMemory = enabled; }
    bool CanDealWithNoMemory() const { return m_DealWithNoMemory; }

    // NOTSA - Get all valid objects with their index - Useful for iteration
    template<typename R = T>
    auto GetAllValidWithIndex() {
        return std::span{ reinterpret_cast<StorageType*>(m_Storage), (size_t)(m_Capacity) }
            | rngv::transform([this](auto&& obj) -> R* { return (R*)(void*)(&obj); })                                 // Convert to object pointer
            | rngv::enumerate                                                                                         // Add index to non-filtered range
            | rngv::filter([this](auto&& p) { return !IsFreeSlotAtIndex(std::get<0>(p)); })                           // Filter out free slots
            | rngv::transform([](auto&& p) -> std::tuple<int32, R&> { return { std::get<0>(p), *std::get<1>(p) }; }); // Convert obj pointer to ref 
    }

    // NOTSA - Get all valid objects - Useful for iteration
    template<typename R = T>
    auto GetAllValid() {
        return GetAllValidWithIndex<R>()
            | rngv::transform([](auto&& p) -> R& { return std::get<1>(p); });
    }

protected:
    void DoFill(byte fill, StorageType* at = nullptr) {
        if (at) {
            memset(at, fill, sizeof(StorageType)); /* One object */
        } else {
            memset(m_Storage, fill, sizeof(StorageType) * m_Capacity); /* Whole storage */
        }
    }

    void CheckFill(byte expected, StorageType* at) {
        StorageType fill;
        std::memset(&fill, expected, sizeof(fill));
        if (std::memcmp(at, &fill, sizeof(fill)) != 0) {
            NOTSA_UNREACHABLE("Use-after-free or buffer over/underflow detected at 0x{:x} (Expected fill was 0x{:x})", LOG_PTR(at), expected);
        }
    }

    int32 FindFreeSlot() const {
        const auto last = m_LastFreeSlot != -1 ? m_LastFreeSlot : 0;
        const auto cap  = m_Capacity;

        // Try [last, cap)
        for (auto i = last; i < cap; i++) {
            if (m_SlotState[i].IsEmpty) {
                return i;
            }
        }

        // Try [0, last)
        for (auto i = 0; i < last; i++) {
            if (m_SlotState[i].IsEmpty) {
                return i;
            }
        }

        // No free slots
        return -1;
    }

private:
    StorageType* m_Storage{};           //!< Storage
    SlotState*   m_SlotState{};         //!< States of each slot
    size_t       m_Capacity{};          //!< Max no. of allocated objects (AKA Size)
    int32        m_LastFreeSlot{ -1 };  //!< Last free slot in the storage
    bool         m_OwnsAllocations{};   //!< If the allocated arrays (`m_Storage` and `m_SlotState` is owned by, if so, we need to free them)
    bool         m_DealWithNoMemory{};  //!< If the caller is expected to be able to handle out-of-memory situations (Used for debugging) (AKA m_bIsLocked)
};
VALIDATE_SIZE(CPool<int32>, 0x14);
