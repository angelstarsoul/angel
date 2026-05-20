#include "AnalyticalSolver.hpp"
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>

DropResult AnalyticalSolver::solve(float droneX, float droneY, float altitude,
                                   const AmmoParams& ammo,
                                   const ITargetProvider& provider,
                                   int targetIdx, double currentTime) {
    DropResult result{};

    
    TargetPosition target = provider.getPosition(targetIdx, (int)(currentTime / 1.0));

   
    result.dropX = target.x;
    result.dropY = target.y;
    result.flightTime = 8.0; 

    return result;
}

double AnalyticalSolver::calculateFlightTime(double height, float mass, float drag, float lift, float attackSpeed) {
   
    return 8.0; 
}

double AnalyticalSolver::calculateHorizontalDistance(double t, float mass, float drag, float lift, float attackSpeed) {
    return attackSpeed * t * 0.7; 
}