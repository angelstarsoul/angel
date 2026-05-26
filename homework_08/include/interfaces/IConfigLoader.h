#pragma once
#include "../Types.h"

class IConfigLoader {
public:
    virtual ~IConfigLoader() = default;
    virtual bool load(const std::string& path) = 0;
    virtual const DroneConfig& getConfig() const = 0;
    virtual const AmmoParams& getAmmo() const = 0;
};