#include <iostream>
#include "Factory.hpp"
#include "MissionProcessor.hpp"

int main() {
    std::cout << "=== Homework 07 - Refactoring ===\n\n";

    
    const std::string configPath  = "homework_07/config.json";
    const std::string targetsPath = "homework_07/targets.json";

    
    IConfigLoader* loader     = createLoader(LoaderType::FILE);
    ITargetProvider* provider = createProvider(ProviderType::JSON, targetsPath);
    IBallisticSolver* solver  = createSolver(SolverType::ANALYTICAL);

    MissionProcessor mission(loader, provider, solver);

    if (!mission.init(configPath)) {
        std::cerr << "Failed to initialize mission" << std::endl;
        delete solver;
        delete provider;
        delete loader;
        return 1;
    }

    std::cout << "Mission started. Targets: " 
              << provider->getTargetCount() << "\n\n";

    int stepCount = 0;
    while (mission.hasNext()) {
        SimulationStep step = mission.step();
        
        std::cout << "Step " << stepCount++
                  << " | Target: " << step.targetIdx
                  << " | Drop: (" << step.drop.dropX << ", " << step.drop.dropY << ")"
                  << " | Flight time: " << step.drop.flightTime << "s\n";
    }

    std::cout << "\nSimulation finished. Total steps: " << stepCount << std::endl;

    
    delete solver;
    delete provider;
    delete loader;

    return 0;
}