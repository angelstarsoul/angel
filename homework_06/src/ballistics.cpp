#include "ballistics.hpp"
#include <cmath>
#include <map>
#include <string>

namespace {
struct AmmoParams {
  double mass_kg;
  double drag;
  double lift;
};

const std::map<std::string, AmmoParams> ammo_db = {{"VOG-17", {0.35, 0.07, 0.0}},
                                                   {"M67", {0.60, 0.10, 0.0}},
                                                   {"RKG-3", {1.20, 0.10, 0.0}},
                                                   {"GLIDING-VOG", {0.45, 0.10, 1.0}},
                                                   {"GLIDING-RKG", {1.40, 0.10, 1.0}}};
}  // namespace

DropSolution compute_drop_solution(const BallisticsInput& input)
{
  DropSolution sol{};
  sol.valid = false;

  if (input.drone_z <= 0.0) {
    sol.message = "error: drone altitude <= 0";
    return sol;
  }
  if (input.attack_speed <= 0.0) {
    sol.message = "error: attack speed <= 0";
    return sol;
  }

  auto it = ammo_db.find(input.ammo_name);
  if (it == ammo_db.end()) {
    sol.message = "error: unknown ammo type: " + input.ammo_name;
    return sol;
  }

  const auto& ammo = it->second;

  double dx = input.target_x - input.drone_x;
  double dy = input.target_y - input.drone_y;
  double dist = std::sqrt(dx * dx + dy * dy);

  if (dist < 1e-6) {
    sol.message = "error: target too close to drone";
    return sol;
  }

  // Покращена балістика
  double t_fall = std::sqrt(2.0 * input.drone_z / 9.81) * (1.0 + ammo.lift * 0.35);
  double horizontal_offset = input.attack_speed * t_fall * 0.78;

  sol.fire_x = input.target_x - (dx / dist) * horizontal_offset;
  sol.fire_y = input.target_y - (dy / dist) * horizontal_offset;
  sol.time_to_impact = t_fall;
  sol.valid = true;
  sol.message = "ok";

  return sol;
}