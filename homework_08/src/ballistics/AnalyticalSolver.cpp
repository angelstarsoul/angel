#include "ballistics/AnalyticalSolver.h"
#include <cmath>

DropSolution AnalyticalSolver::solve(const DroneConfig& config,
                                     const AmmoParams& ammo,
                                     const ITargetProvider& provider,
                                     int targetIdx, double currentTime) {
    DropSolution sol{};
    sol.valid = false;

    TargetPosition target = provider.getPosition(targetIdx, static_cast<int>(currentTime));

    double dx = target.x - config.start_x;
    double dy = target.y - config.start_y;
    double dist = std::sqrt(dx*dx + dy*dy);

    if (dist < 1e-6) {
        sol.message = "target too close";
        return sol;
    }

    sol.fire_x = target.x;
    sol.fire_y = target.y;
    sol.time_to_impact = 8.0; // заглушка
    sol.valid = true;
    sol.message = "ok";

    return sol;
}