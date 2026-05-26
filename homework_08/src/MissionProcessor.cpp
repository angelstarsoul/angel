#include "MissionProcessor.h"
#include "interfaces/IConfigLoader.h"
#include "interfaces/ITargetProvider.h"
#include "interfaces/IBallisticSolver.h"

MissionProcessor::MissionProcessor(std::unique_ptr<IConfigLoader> config,
                                   std::unique_ptr<ITargetProvider> provider,
                                   std::unique_ptr<IBallisticSolver> solver)
    : configLoader(std::move(config)),
      targetProvider(std::move(provider)),
      solver(std::move(solver)) {}

bool MissionProcessor::init(const std::string& configPath) {
    if (!configLoader || !targetProvider || !solver) return false;
    return configLoader->load(configPath);
}

bool MissionProcessor::hasMoreTargets() const {
    return currentTargetIndex < static_cast<size_t>(targetProvider->getTargetCount());
}

DropSolution MissionProcessor::processNextTarget() {
    if (!hasMoreTargets()) {
        return DropSolution{0, 0, 0, false, "no more targets"};
    }

    const DroneConfig& cfg = configLoader->getConfig();
    const AmmoParams& ammo = configLoader->getAmmo();

    DropSolution result = solver->solve(cfg, ammo, *targetProvider,
                                        static_cast<int>(currentTargetIndex), 0.0);

    ++currentTargetIndex;
    return result;
}