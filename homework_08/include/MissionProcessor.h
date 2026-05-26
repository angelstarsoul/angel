#pragma once
#include "interfaces/IConfigLoader.h"
#include "interfaces/ITargetProvider.h"
#include "interfaces/IBallisticSolver.h"
#include <memory>

class MissionProcessor {
public:
    MissionProcessor(std::unique_ptr<IConfigLoader> config,
                     std::unique_ptr<ITargetProvider> provider,
                     std::unique_ptr<IBallisticSolver> solver);

    bool init(const std::string& configPath);
    bool hasMoreTargets() const;
    DropSolution processNextTarget();

private:
    std::unique_ptr<IConfigLoader> configLoader;
    std::unique_ptr<ITargetProvider> targetProvider;
    std::unique_ptr<IBallisticSolver> solver;
    size_t currentTargetIndex = 0;
};