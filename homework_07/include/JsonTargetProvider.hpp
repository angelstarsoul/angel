#pragma once
#include "ITargetProvider.hpp"
#include <vector>
#include <string>

class JsonTargetProvider : public ITargetProvider {
public:
    JsonTargetProvider(const std::string& targetsPath);
    ~JsonTargetProvider() override;

    int getTargetCount() const override;
    int getTimeSteps() const override;
    TargetPosition getPosition(int targetIdx, int timeStep) const override;

private:
    std::vector<std::vector<TargetPosition>> targets;
    int timeSteps = 0;
};