#pragma once
#include "IConfigLoader.hpp"
#include "ITargetProvider.hpp"
#include "IBallisticSolver.hpp"
#include <vector>

struct SimulationStep {
    float droneX, droneY;
    float direction;
    int targetIdx;
    DropResult drop;
};

class MissionProcessor {
public:
    MissionProcessor(IConfigLoader* loader, ITargetProvider* provider, IBallisticSolver* solver);
    ~MissionProcessor();

    bool init(const std::string& configPath);
    bool hasNext() const;
    SimulationStep step();
    void reset();
    void changeSolver(IBallisticSolver* newSolver);

private:
    IConfigLoader* configLoader = nullptr;
    ITargetProvider* targetProvider = nullptr;
    IBallisticSolver* solver = nullptr;

    int currentTarget = 0;
    double currentTime = 0.0;
    bool initialized = false;
};