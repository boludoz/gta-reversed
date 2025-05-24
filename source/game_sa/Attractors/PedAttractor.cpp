#include "StdInc.h"

#include "PedAttractor.h"

#include "Tasks/TaskTypes/TaskComplexGoToAttractor.h"
#include "Tasks/TaskTypes/TaskComplexWaitAtAttractor.h"
#include "Tasks/TaskTypes/TaskComplexUseAttractor.h"
#include "Tasks/TaskTypes/TaskComplexUsePairedAttractor.h"
#include "Tasks/TaskTypes/TaskSimpleStandStill.h"

void CPedAttractor::InjectHooks() {
    RH_ScopedVirtualClass(CPedAttractor, 0x86C538, 6);
    RH_ScopedCategory("Attractors");

    RH_ScopedInstall(Constructor, 0x5EDFB0);
    RH_ScopedInstall(Destructor, 0x5EC410);

    RH_ScopedInstall(SetTaskForPed, 0x5EECA0);
    RH_ScopedInstall(RegisterPed, 0x5EEE30);
    RH_ScopedInstall(DeRegisterPed, 0x5EC5B0);
    RH_ScopedInstall(IsRegisteredWithPed, 0x5EB4C0);
    RH_ScopedInstall(IsAtHeadOfQueue, 0x5EB530);
    RH_ScopedInstall(GetTaskForPed, 0x5EC500);
    RH_ScopedInstall(GetQueueSlot, 0x5EB550);
    //RH_ScopedInstall(GetNoOfRegisteredPeds, 0xdeadbeef, { .reversed = false }); // Address incorrect
    RH_ScopedInstall(GetHeadOfQueue, 0x5EB590);
    RH_ScopedInstall(GetTailOfQueue, 0x5EB5B0);
    RH_ScopedInstall(HasEmptySlot, 0x5EAF10);
    //RH_ScopedInstall(ComputeFreeSlot, 0x0, { .reversed = false });
    RH_ScopedInstall(ComputeDeltaPos, 0x5E9600);
    RH_ScopedInstall(ComputeDeltaHeading, 0x5E9640);
    RH_ScopedInstall(ComputeAttractTime, 0x5E95E0);
    RH_ScopedOverloadedInstall(ComputeAttractPos, "v", 0x5EA110, void(CPedAttractor::*)(int32, CVector&));
    RH_ScopedOverloadedInstall(ComputeAttractHeading, "v", 0x5EA1C0, void(CPedAttractor::*)(int32, float&));
    RH_ScopedInstall(BroadcastDeparture, 0x5EF160);
    RH_ScopedInstall(BroadcastArrival, 0x5EEF80);
    RH_ScopedInstall(AbortPedTasks, 0x5EAF60, { .reversed = false });
}

// 0x5EAFD0
void* CPedAttractor::operator new(unsigned size) {
    return GetPedAttractorPool()->New();
}

// 0x5EAFE0
void CPedAttractor::operator delete(void* object) {
    GetPedAttractorPool()->Delete(static_cast<CPedAttractor*>(object));
}

// 0x5EDFB0
CPedAttractor::CPedAttractor(
    C2dEffectPedAttractor* fx,
    CEntity*               entity,
    eMoveState             moveState,
    size_t                 maxNoOfPeds,
    float                  spacing,
    float                  achieveQueueTime,
    float                  achieveQueueShuffleTime,
    float                  arriveRange,
    float                  headingRange,
    float                  deltaPos,
    float                  deltaHeading
) :
    m_Fx{fx},
    m_Entity{entity},
    m_MoveState{moveState},
    m_MaxNumPeds{maxNoOfPeds},
    m_Spacing{spacing},
    m_AchieveQueueTime{achieveQueueTime},
    m_AchieveQueueShuffleTime{achieveQueueShuffleTime},
    m_ArriveRange{arriveRange},
    m_HeadingRange{headingRange},
    m_DeltaPos{deltaPos},
    m_DeltaHeading{deltaHeading}
{
    const CMatrix mat = entity
        ? entity->GetMatrix()
        : CMatrix::Unity();
    m_Pos      = CPedAttractorManager::ComputeEffectPos(fx, mat);
    m_QueueDir = CPedAttractorManager::ComputeEffectQueueDir(fx, mat);
    m_UseDir   = CPedAttractorManager::ComputeEffectUseDir(fx, mat);

    strcpy_s(m_ScriptName, fx->m_szScriptName);
}

void CPedAttractor::Shutdown() {
    ms_tasks.clear();
}

// 0x5EECA0
void CPedAttractor::SetTaskForPed(CPed* ped, CTask* task) {
    if (const auto pair = rng::find(m_PedTaskPairs, ped, &CPedTaskPair::Ped); pair != m_PedTaskPairs.end()) {
        if (!pair->UsedTask) { // 0x5EED79
            ms_tasks.erase(rng::find(ms_tasks, pair->Task)); // 0x5EEDA0, 0x5EEDAD
            delete pair->Task; // 0x5EEDD1
        }
        pair->Task     = task;
        pair->UsedTask = false;
    } else {
        m_PedTaskPairs.emplace_back(CPedTaskPair{ .Ped = ped, .Task = task });
    }
}

// 0x5EEE30
bool CPedAttractor::RegisterPed(CPed* ped) {
    if (const auto it = rng::find(m_AttractPeds, ped); it != m_AttractPeds.end()) {
        m_AttractPeds.erase(it);
        return false;
    }
    if (m_AttractPeds.size() + m_ArrivedPeds.size() >= m_MaxNumPeds) {
        return false;
    }
    m_ArrivedPeds.emplace_back(ped);
    const auto idx = (int32)(m_ArrivedPeds.size() - 1);
    SetTaskForPed(ped, new CTaskComplexGoToAttractor{
        this,
        ComputeAttractPos(idx),
        ComputeAttractHeading(idx),
        m_AchieveQueueTime,
        idx,
        m_MoveState
    });
    return true;
}

// 0x5EC5B0
bool CPedAttractor::DeRegisterPed(CPed* ped) {
    m_PedTaskPairs.erase(rng::find(m_PedTaskPairs, ped, &CPedTaskPair::Ped));
    if (const auto it = rng::find(m_ArrivedPeds, ped); it != m_ArrivedPeds.end()) { // inverted (!)
        m_AttractPeds.erase(it);
        return true;
    }
    return BroadcastDeparture(ped);
}

// 0x5EB4C0
bool CPedAttractor::IsRegisteredWithPed(const CPed* ped) const {
    return rng::contains(m_AttractPeds, ped)
        || rng::contains(m_ArrivedPeds, ped);
}

// 0x5EB530
bool CPedAttractor::IsAtHeadOfQueue(CPed* ped) {
    return !m_ArrivedPeds.empty() && m_ArrivedPeds.front() == ped; // NOTE/BUGFIX: Check if the array is empty
}

// 0x5EC500
CTask* CPedAttractor::GetTaskForPed(CPed* ped) {
    const auto it = rng::find(m_PedTaskPairs, ped, &CPedTaskPair::Ped);
    if (it == m_PedTaskPairs.end()) {
        return nullptr;
    }
    if (!it->UsedTask) {
        ms_tasks.erase(rng::find(ms_tasks, it->Task));
    }
    it->UsedTask = true;
    return it->Task;
}

// 0x5EB550
int32 CPedAttractor::GetQueueSlot(const CPed* ped) {
    assert(rng::find(m_ArrivedPeds, ped) != m_ArrivedPeds.end());
    return rng::distance(m_ArrivedPeds.begin(), rng::find(m_ArrivedPeds, ped));
}

// 0x5EB590
CPed* CPedAttractor::GetHeadOfQueue() const {
    return m_ArrivedPeds.empty()
        ? nullptr
        : m_ArrivedPeds.front();
}

// 0x5EB5B0
CPed* CPedAttractor::GetTailOfQueue() const {
    return m_ArrivedPeds.empty()
        ? nullptr
        : m_ArrivedPeds.back();
}

int32 CPedAttractor::ComputeFreeSlot() {
    assert(0);
    return 0;
}

// 0x5E9600
float CPedAttractor::ComputeDeltaPos() const {
    return CGeneral::GetRandomNumberInRange(-m_DeltaPos, m_DeltaPos);
}

// 0x5E9640
float CPedAttractor::ComputeDeltaHeading() const {
    return CGeneral::GetRandomNumberInRange(-m_DeltaHeading, m_DeltaHeading);
}

// inlined
// 0x5E95E0
void CPedAttractor::ComputeAttractTime(int32 unused, bool time1_or_time2, float& outTime) const {
    if (time1_or_time2)
        outTime = m_AchieveQueueShuffleTime;
    else
        outTime = m_AchieveQueueTime;
}

// 0x5EA110
void CPedAttractor::ComputeAttractPos(int32 pedId, CVector& outPos) {
    if (m_Fx) {
        outPos = m_Pos - m_Spacing * (float)pedId * m_QueueDir;

        if (pedId) {
            outPos.x += ComputeDeltaPos();
            outPos.y += ComputeDeltaPos();
        }
    }
}

// bQueue - bad name?
// 0x5EA1C0
void CPedAttractor::ComputeAttractHeading(int32 bQueue, float& heading) {
    if (m_Fx) {
        if (bQueue)
            m_UseDir = m_QueueDir;

        heading = CGeneral::GetRadianAngleBetweenPoints(m_UseDir.x, m_UseDir.y, 0.0f, 0.0f);
        if (bQueue)
            heading += CPedAttractor::ComputeDeltaHeading();
    }
}

// 0x5EF160
bool CPedAttractor::BroadcastDeparture(CPed* ped) {
    const auto it = rng::find(m_AttractPeds, ped);
    if (it == m_AttractPeds.end()) {
        return false;
    }
    const auto idx = rng::distance(m_AttractPeds.begin(), it);
    for (auto i = idx + 1; i < (int32)(m_AttractPeds.size()); ++i) { // 0x5EF1C6
        SetTaskForPed(m_AttractPeds[i], new CTaskComplexSequence{
            new CTaskSimpleStandStill{ 2000 * i },
            new CTaskComplexGoToAttractor{ this, ComputeAttractPos(i), ComputeAttractHeading(i), m_AchieveQueueShuffleTime, i, PEDMOVE_WALK },
        });
    }
    m_PedTaskPairs.erase(rng::find(m_PedTaskPairs, ped, &CPedTaskPair::Ped)); // 0x5EF2F6
    m_ArrivedPeds.erase(it); // 0x5EF334
    for (auto* const attractedPed : m_AttractPeds) { // 0x5EF371
        const auto n = (int32)(m_ArrivedPeds.size());
        SetTaskForPed(attractedPed, new CTaskComplexGoToAttractor({
            this,
            ComputeAttractPos(n),
            ComputeAttractHeading(n),
            m_AchieveQueueTime,
            n,
            PEDMOVE_WALK
        }));
    }
    return true;
}

// 0x5EEF80
bool CPedAttractor::BroadcastArrival(CPed* ped) {
    if (!rng::contains(m_ArrivedPeds, ped)) {
        m_ArrivedPeds.emplace_back(ped); // 0x5EEFCB
        m_AttractPeds.erase(rng::find(m_AttractPeds, ped)); // 0x5EF002
        for (auto* const attractedPed : m_AttractPeds) { // 0x5EF098
            const auto idx = (int32)(m_ArrivedPeds.size());
            SetTaskForPed(attractedPed, new CTaskComplexGoToAttractor{ // 0x5EF090
                this,
                ComputeAttractPos(idx),
                ComputeAttractHeading(idx),
                m_AchieveQueueTime,
                idx,
                m_MoveState
            });
        }
    }

    if (!IsAtHeadOfQueue(ped)) { // 0x5EF129
        SetTaskForPed(ped, new CTaskComplexWaitAtAttractor{ this, GetQueueSlot(ped) });
    } else if (GetType() == PED_ATTRACTOR_SCRIPTED) { // 0x5EF0D6 - inverted (!)
        SetTaskForPed(ped, new CTaskComplexUsePairedAttractor{ this });
    } else { // 0x5EF0FA
        SetTaskForPed(ped, new CTaskComplexUseAttractor{ this });
    }

    return true;
}

// 0x5EAF60
void CPedAttractor::AbortPedTasks() {
    for (auto& p : m_PedTaskPairs) {
        p.Ped = nullptr;
        delete std::exchange(p.Task, nullptr);
        p.Slot = TASK_SECONDARY_INVALID;
    }
    // TODO/NOTE: Why not clear the array?
}
