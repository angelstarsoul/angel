#pragma once
#include "../interfaces/IBallisticSolver.h"

class AnalyticalSolver : public IBallisticSolver {
public:
    DropSolution solve(const DroneConfig& config,
                       const AmmoParams& ammo,
                       const ITargetProvider& provider,
                       int targetIdx, double currentTime) override;
};