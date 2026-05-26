#include "MissionProcessor.h"
#include "interfaces/IConfigLoader.h"
#include "interfaces/ITargetProvider.h"
#include "interfaces/IBallisticSolver.h"
#include "config/FileConfigLoader.h"
#include "providers/JsonTargetProvider.h"
#include "ballistics/AnalyticalSolver.h"
#include <iostream>
#include <memory>

int main() {
    std::cout << "=== Homework 08 - STL + Clean Structure ===\n\n";

    auto configLoader = std::make_unique<FileConfigLoader>();
    auto targetProvider = std::make_unique<JsonTargetProvider>("homework_08/data/targets.json");
    auto solver = std::make_unique<AnalyticalSolver>();

    MissionProcessor processor(std::move(configLoader),
                               std::move(targetProvider),
                               std::move(solver));

    if (!processor.init("homework_08/data/config.json")) {
        std::cerr << "Failed to initialize mission" << std::endl;
        return 1;
    }

    std::cout << "Mission started successfully!\n\n";

    int step = 0;
    while (processor.hasMoreTargets()) {
        DropSolution result = processor.processNextTarget();
        std::cout << "Step " << step++ 
                  << " | Drop: (" << result.fire_x << ", " << result.fire_y 
                  << ") | Time: " << result.time_to_impact 
                  << "s | Status: " << result.message << "\n";
    }

    std::cout << "\nSimulation completed.\n";
    return 0;
}