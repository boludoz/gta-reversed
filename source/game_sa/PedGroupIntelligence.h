/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <concepts>
#include <PedGroup.h>
#include "PedTaskPair.h"
#include "DecisionMakerTypes.h"
#include <TaskManager.h>
#include "Tasks/TaskTypes/TaskSimpleNone.h"
#include "Tasks/Allocators/PedGroup/PedGroupDefaultTaskAllocatorType.h"

class CPed;
class CTask;
class CGroupEventHandler;
class CPedGroupDefaultTaskAllocator;
class CTaskAllocator;
class CEvent;
class CPedGroup;
class CEventGroupEvent;

class CPedGroupIntelligence {
    using PedTaskPairs = std::array<CPedTaskPair, TOTAL_PED_GROUP_MEMBERS>;
public:
    static void InjectHooks();

    CPedGroupIntelligence(CPedGroup* owner);
    ~CPedGroupIntelligence();

    void Flush();

    bool            AddEvent(CEvent* event);
    void            ComputeDefaultTasks(CPed* ped);
    CTaskAllocator* ComputeEventResponseTasks();
    void            ComputeScriptCommandTasks();
    static void     FlushTasks(PedTaskPairs& taskPairs, CPed* ped);

    //! @notsa
    CPedTaskPair*  GetPedsTaskPair(CPed* ped, PedTaskPairs& taskPairs) const;

    CTask*         GetTask(CPed* ped, PedTaskPairs& taskPairs) const;
    CTask*         GetTaskMain(CPed* ped);
    CTask*         GetTaskDefault(CPed* ped);
    CTask*         GetTaskScriptCommand(CPed* ped);
    CTask*         GetTaskSecondary(CPed* ped);
    eSecondaryTask GetTaskSecondarySlot(CPed* ped);

    bool IsCurrentEventValid();
    bool IsGroupResponding();
    void Process();
    void ProcessIgnorePlayerGroup();
    void ReportAllBarScriptTasksFinished();
    void ReportAllTasksFinished(PedTaskPairs& taskPairs);
    //void ReportAllTasksFinished();
    bool ReportFinishedTask(const CPed* ped, const CTask* task, PedTaskPairs& taskpair);
    bool ReportFinishedTask(const CPed* ped, const CTask* task);
    void SetDefaultTaskAllocator(const CPedGroupDefaultTaskAllocator& ta);
    void SetDefaultTaskAllocatorType(ePedGroupDefaultTaskAllocatorType taType);

    /*!
    * @addr 0x5F8510
    * @note The tasks passed to this function **shouldn't** be `new`-d, but rather stack allocated!
    * @note Also, it's often inlined into an unused `CTaskSimpleNone` and `SetTask` call.
    */
    void SetEventResponseTask(
        CPed*        ped,
        bool         hasMainTask,

        const CTask& mainTask,
        bool         hasSecondaryTask = false,

        const CTask&   secondaryTask = CTaskSimpleNone{},
        eSecondaryTask slot          = TASK_SECONDARY_INVALID
    );
    //! @notsa
    void SetEventResponseTask(CPed* ped, const CTask& task) { SetEventResponseTask(ped, true, task); }
    void SetEventResponseTaskAllocator(CTaskAllocator* ta);
    void SetGroupDecisionMakerType(eDecisionMakerType t) { m_DecisionMakerType = t; }
    void SetPrimaryTaskAllocator(CTaskAllocator* ta);

    auto GetCurrentEvent()         { return m_CurrentEvent; }
    auto GetHighestPriorityEvent() { return m_HighestPriorityEvent; }

    template<std::derived_from<CEvent> T>
    auto AddEvent(T event) { // TODO: Remove in final
        return AddEvent(&event);
    }

    //! `task` shouldn't be `new`-d, but rather stack allocated!
    void SetTask(CPed* ped, const CTask& task, PedTaskPairs& taskPairs, eSecondaryTask slot = TASK_SECONDARY_INVALID, bool force = false) const;
    void SetDefaultTask(CPed* ped, const CTask& task);
    void SetScriptCommandTask(CPed* ped, const CTask& task);

    auto&& GetPedTaskPairs(this auto&& self)          { return self.m_PedTaskPairs; }
    auto&& GetSecondaryPedTaskPairs(this auto&& self) { return self.m_SecondaryPedTaskPairs; }
    auto&& GetDefaultPedTaskPairs(this auto&& self)   { return self.m_DefaultPedTaskPairs; }

    auto&& GetPedGroup(this auto&& self) { return *self.m_pPedGroup; }

private:
    bool ShouldSetHighestPriorityEventAsCurrent();

private: // Wrappers for hooks
    // 0x5F7250
    CPedGroupIntelligence* Constructor() {
        this->CPedGroupIntelligence::CPedGroupIntelligence(nullptr);
        return this;
    }

private:
    CPedGroup*                           m_pPedGroup{};
    CEventGroupEvent*                    m_CurrentEvent{};
    CEventGroupEvent*                    m_HighestPriorityEvent{};
    PedTaskPairs                         m_PedTaskPairs{};
    PedTaskPairs                         m_SecondaryPedTaskPairs{};
    PedTaskPairs                         m_ScriptCommandPedTaskPairs{};
    PedTaskPairs                         m_DefaultPedTaskPairs{};
    const CPedGroupDefaultTaskAllocator* m_DefaultTaskAllocator{};
    CTaskAllocator*                      m_PrimaryTaskAllocator{};
    CTaskAllocator*                      m_EventResponseTaskAllocator{};
    eDecisionMakerType                   m_DecisionMakerType{ eDecisionMakerType::UNKNOWN };
    int32                                m_TaskSeqId{ -1 }; // Used in CTaskSequences::ms_taskSequence
};
VALIDATE_SIZE(CPedGroupIntelligence, 0x2A0);
