#include "MissionProcessor.hpp"
#include <iostream>

MissionProcessor::MissionProcessor(IConfigLoader* loader, ITargetProvider* provider, IBallisticSolver* solver)
    : configLoader(loader), targetProvider(provider), solver(solver) {}

MissionProcessor::~MissionProcessor() = default;

bool MissionProcessor::init(const std::string& configPath) {
    if (!configLoader || !targetProvider || !solver) return false;
    if (!configLoader->load(configPath)) return false;

    reset();
    initialized = true;
    return true;
}

bool MissionProcessor::hasNext() const {
    return initialized && currentTarget < targetProvider->getTargetCount();
}

SimulationStep MissionProcessor::step() {
    SimulationStep step{};

    if (!hasNext()) return step;

    const DroneConfig& cfg = configLoader->getConfig();
    const AmmoParams& ammo = configLoader->getAmmo();

    step.droneX = cfg.startX;
    step.droneY = cfg.startY;
    step.targetIdx = currentTarget;
    step.direction = cfg.initialDirection;

    step.drop = solver->solve(cfg.startX, cfg.startY, cfg.altitude,
                              ammo, *targetProvider, currentTarget, currentTime);

    currentTime += 1.0;
    if (currentTime > 60.0) { 
        currentTime = 0.0;
        ++currentTarget;
    }

    return step;
}

void MissionProcessor::reset() {
    currentTarget = 0;
    currentTime = 0.0;
}

void MissionProcessor::changeSolver(IBallisticSolver* newSolver) {
    solver = newSolver;
}