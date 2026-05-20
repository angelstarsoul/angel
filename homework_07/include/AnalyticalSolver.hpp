#pragma once
#include "IBallisticSolver.hpp"
#include "IConfigLoader.hpp"

class AnalyticalSolver : public IBallisticSolver {
public:
    DropResult solve(float droneX, float droneY, float altitude,
                     const AmmoParams& ammo,
                     const ITargetProvider& provider,
                     int targetIdx, double currentTime) override;

private:
    double calculateFlightTime(double height, float mass, float drag, float lift, float attackSpeed);
    double calculateHorizontalDistance(double t, float mass, float drag, float lift, float attackSpeed);
};