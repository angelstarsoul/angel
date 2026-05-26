#pragma once
#include <string>
#include <vector>

struct AmmoParams {
    std::string name;
    double mass_kg = 0.0;
    double drag = 0.0;
    double lift = 0.0;
};

struct DroneConfig {
    double start_x = 0.0;
    double start_y = 0.0;
    double altitude = 0.0;
    double attack_speed = 0.0;
    double acceleration_path = 0.0;
    double angular_speed = 0.0;
    double turn_threshold = 0.0;
    std::string ammo_name;
};

struct TargetPosition {
    double x = 0.0;
    double y = 0.0;
};

struct DropSolution {
    double fire_x = 0.0;
    double fire_y = 0.0;
    double time_to_impact = 0.0;
    bool valid = false;
    std::string message;
};