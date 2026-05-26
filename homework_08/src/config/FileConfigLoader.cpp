#include "config/FileConfigLoader.h"
#include "external/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool FileConfigLoader::load(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cerr << "Cannot open config file: " << path << std::endl;
        return false;
    }

    json j;
    f >> j;

    config.start_x = j["drone"]["position"]["x"];
    config.start_y = j["drone"]["position"]["y"];
    config.altitude = j["drone"]["altitude"];
    config.attack_speed = j["drone"]["attackSpeed"];
    config.acceleration_path = j["drone"]["accelerationPath"];
    config.ammo_name = j["ammo"];

    // Завантаження ammo
    std::ifstream fa("homework_08/data/ammo.json");
    if (fa.is_open()) {
        json ja;
        fa >> ja;
        for (const auto& item : ja) {
            if (item["name"] == config.ammo_name) {
                ammo.name = item["name"];
                ammo.mass_kg = item["mass"];
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