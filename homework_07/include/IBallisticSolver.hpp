#pragma once
#include "IConfigLoader.hpp"    
#include "ITargetProvider.hpp"

struct DropResult {
    float dropX = 0.0f;
    float dropY = 0.0f;
    float flightTime = 0.0f;
};

class IBallisticSolver {
public:
    virtual ~IBallisticSolver() = default;
    virtual DropResult solve(float droneX, float droneY, float altitude,
                             const AmmoParams& ammo,         
                             const ITargetProvider& provider,
                             int targetIdx, double currentTime) = 0;
};