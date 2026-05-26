#pragma once
#include "../Types.h"
#include "ITargetProvider.h"   // ← Повний include!

class IBallisticSolver {
public:
    virtual ~IBallisticSolver() = default;
    virtual DropSolution solve(const DroneConfig& config,
                               const AmmoParams& ammo,
                               const ITargetProvider& provider,
                               int targetIdx, double currentTime) = 0;
};