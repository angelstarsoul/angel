#include "providers/JsonTargetProvider.h"
#include "external/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

JsonTargetProvider::JsonTargetProvider(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cerr << "Cannot open targets.json" << std::endl;
        return;
    }

    json j;
    f >> j;

    timeSteps = j["timeSteps"];
    int count = j["targetCount"];

    targets.resize(count);
    for (int i = 0; i < count; ++i) {
        targets[i].resize(timeSteps);
        for (int k = 0; k < timeSteps; ++k) {
            targets[i][k].x = j["targets"][i]["positions"][k]["x"];
            targets[i][k].y = j["targets"][i]["positions"][k]["y"];
        }
    }
}

int JsonTargetProvider::getTargetCount() const { return targets.size(); }
int JsonTargetProvider::getTimeSteps() const { return timeSteps; }

TargetPosition JsonTargetProvider::getPosition(int targetIdx, int timeStep) const {
    if (targetIdx < 0 || targetIdx >= (int)targets.size() ||
        timeStep < 0 || timeStep >= timeSteps) {
        return {0.0, 0.0};
    }
    return targets[targetIdx][timeStep];
}