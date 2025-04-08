#pragma once

#include "Pool.h"

class CNodeRoutePool : public CPool<CNodeRoute> {
public:
    static void InjectHooks() {
        RH_ScopedClass(CNodeRoutePool);
        RH_ScopedCategory("Pools");

        RH_ScopedInstall(New, 0x0041B710);
    }

public:
    using CPool::CPool;
};
