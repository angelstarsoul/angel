#pragma once
#include "../interfaces/ITargetProvider.h"
#include <vector>

class JsonTargetProvider : public ITargetProvider {
public:
    explicit JsonTargetProvider(const std::string& path);
    int getTargetCount() const override;
    int getTimeSteps() const override;
    TargetPosition getPosition(int targetIdx, int timeStep) const override;

private:
    std::vector<std::vector<TargetPosition>> targets;
    int timeSteps = 0;
};