#pragma once
#include <string>

struct AmmoParams {
    std::string name;
    float mass = 0.0f;
    float drag = 0.0f;
    float lift = 0.0f;
};

struct DroneConfig {
    float startX = 0.0f, startY = 0.0f;
    float altitude = 0.0f;
    float initialDirection = 0.0f;
    float attackSpeed = 0.0f;
    float accelerationPath = 0.0f;
    float angularSpeed = 0.0f;
    float turnThreshold = 0.0f;
    std::string ammoName;
    float arrayTimeStep = 1.0f;
    float simTimeStep = 0.1f;
    float hitRadius = 2.0f;
};

class IConfigLoader {
public:
    virtual ~IConfigLoader() = default;
    virtual bool load(const std::string& configPath) = 0;
    virtual const DroneConfig& getConfig() const = 0;
    virtual const AmmoParams& getAmmo() const = 0;
};