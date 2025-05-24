#pragma once

#include <Base.h>
#include <PluginBase.h>
#include <reversiblehooks/ReversibleHooks.h>

#include "./PedGroupDefaultTaskAllocator.h"
#include "TaskComplexBeStill.h"

class NOTSA_EXPORT_VTABLE CPedGroupDefaultTaskAllocatorStandStill final : public CPedGroupDefaultTaskAllocator {
public:
    /* no virtual destructor */

    // 0x5F64D0
    ePedGroupDefaultTaskAllocatorType GetType() const override { return ePedGroupDefaultTaskAllocatorType::STAND_STILL; };

    // 0x5F6DA0
    void AllocateDefaultTasks(CPedGroup* pedGroup, CPed* ped) const override {
        for (auto& tp : pedGroup->GetIntelligence().GetDefaultPedTaskPairs()) {
            if (!tp.Ped) {
                continue;
            }
            if (ped && tp.Ped != ped) {
                continue;
            }
            assert(!tp.Task);
            tp.Task = new CTaskComplexBeStill{}; // Skipping the unnecessary leader check because they both get the same task
            if (notsa::IsFixBugs()) {
                if (ped) {
                    break; // There are no duplicate entries in the array, so we can stop now
                }
            }
        }
    };

public:
    static inline void InjectHooks() {
        RH_ScopedVirtualClass(CPedGroupDefaultTaskAllocatorStandStill, 0x86C76C, 2);
        RH_ScopedCategory("Tasks/Allocators/PedGroup");

        RH_ScopedVMTInstall(AllocateDefaultTasks, 0x5F6DA0);
        RH_ScopedVMTInstall(GetType, 0x5F64D0);
    }
};
VALIDATE_SIZE(CPedGroupDefaultTaskAllocatorStandStill, sizeof(void*)); /* vtable only */
