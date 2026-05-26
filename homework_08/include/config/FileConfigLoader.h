#pragma once
#include "../interfaces/IConfigLoader.h"

class FileConfigLoader : public IConfigLoader {
public:
    bool load(const std::string& path) override;
    const DroneConfig& getConfig() const override;
    const AmmoParams& getAmmo() const override;

private:
    DroneConfig config;
    AmmoParams ammo;
};