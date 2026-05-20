#pragma once
#include "IConfigLoader.hpp"
#include <string>

class FileConfigLoader : public IConfigLoader {
public:
    bool load(const std::string& configPath) override;
    const DroneConfig& getConfig() const override;
    const AmmoParams& getAmmo() const override;

private:
    DroneConfig config;
    AmmoParams ammo;
};