#include "JsonTargetProvider.hpp"
#include "external/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

JsonTargetProvider::JsonTargetProvider(const std::string& targetsPath) {
    std::ifstream f(targetsPath);
    if (!f.is_open()) {
        std::cerr << "Cannot open targets.json" << std::endl;
        return;
    }

    json j;
    f >> j;

    timeSteps = j["timeSteps"];
    int targetCount = j["targetCount"];

    targets.resize(targetCount);
    for (int i = 0; i < targetCount; ++i) {
        targets[i].resize(timeSteps);
        for (int k = 0; k < timeSteps; ++k) {
            targets[i][k].x = j["targets"][i]["positions"][k]["x"];
            targets[i][k].y = j["targets"][i]["positions"][k]["y"];
        }
    }
}

JsonTargetProvider::~JsonTargetProvider() = default;

int JsonTargetProvider::getTargetCount() const { return targets.size(); }
int JsonTargetProvider::getTimeSteps() const { return timeSteps; }

TargetPosition JsonTargetProvider::getPosition(int targetIdx, int timeStep) const {
    if (targetIdx < 0 || targetIdx >= (int)targets.size() ||
        timeStep < 0 || timeStep >= timeSteps) {
        return {0.0f, 0.0f};
    }
    return targets[targetIdx][timeStep];
}