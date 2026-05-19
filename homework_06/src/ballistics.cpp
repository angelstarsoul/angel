#include "ballistics.hpp"
#include <cmath>
#include <map>

namespace {

struct AmmoParams {
  double mass_kg;
  double drag_coeff;
  double fall_time_factor;
};

const std::map<std::string, AmmoParams> ammo_db = {
  {"VOG-17", {0.35, 0.8, 1.0}}, {"VOG-25", {0.25, 0.75, 0.95}},
 
};

}  

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
  double horizontal_distance = std::sqrt(dx * dx + dy * dy);

  
  double t_fall = std::sqrt(2.0 * input.drone_z / 9.81) * ammo.fall_time_factor;

  
  double drop_offset = input.attack_speed * t_fall;

  sol.fire_x = input.target_x - (dx / horizontal_distance) * drop_offset;
  sol.fire_y = input.target_y - (dy / horizontal_distance) * drop_offset;
  sol.time_to_impact = t_fall;
  sol.valid = true;
  sol.message = "ok";

  return sol;
}