#include "FileConfigLoader.hpp"
#include "external/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool FileConfigLoader::load(const std::string& configPath) {
    std::ifstream f(configPath);
    if (!f.is_open()) {
        std::cerr << "Cannot open config.json" << std::endl;
        return false;
    }

    json j;
    f >> j;

    config.startX = j["drone"]["position"]["x"];
    config.startY = j["drone"]["position"]["y"];
    config.altitude = j["drone"]["altitude"];
    config.initialDirection = j["drone"]["initialDirection"];
    config.attackSpeed = j["drone"]["attackSpeed"];
    config.accelerationPath = j["drone"]["accelerationPath"];
    config.angularSpeed = j["drone"]["angularSpeed"];
    config.turnThreshold = j["drone"]["turnThreshold"];
    config.ammoName = j["ammo"];
    config.arrayTimeStep = j["targetArrayTimeStep"];
    config.simTimeStep = j["simulation"]["timeStep"];
    config.hitRadius = j["simulation"]["hitRadius"];


    std::ifstream fa("ammo.json");
    if (fa.is_open()) {
        json ja;
        fa >> ja;
        for (const auto& item : ja) {
            if (item["name"] == config.ammoName) {
                ammo.name = item["name"];
                ammo.mass = item["mass"];
                ammo.drag = item["drag"];
                ammo.lift = item["lift"];
                break;
            }
        }
    }

    return true;
}

const DroneConfig& FileConfigLoader::getConfig() const { return config; }
const AmmoParams& FileConfigLoader::getAmmo() const { return ammo; }