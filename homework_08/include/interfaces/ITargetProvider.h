#pragma once
#include "../Types.h"
#include <vector>

class ITargetProvider {
public:
    virtual ~ITargetProvider() = default;
    virtual int getTargetCount() const = 0;
    virtual int getTimeSteps() const = 0;
    virtual TargetPosition getPosition(int targetIdx, int timeStep) const = 0;
};