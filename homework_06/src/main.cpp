#include "ballistics.hpp"
#include "external/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "Usage: ballistics_cli <input_file.json>\n";
    return 1;
  }

  std::string filename = argv[1];
  std::cout << "=== Ballistics Calculator ===\n";
  std::cout << "Input file: " << filename << "\n\n";

  std::ifstream f(filename);
  if (!f.is_open()) {
    std::cerr << "Error: cannot open file " << filename << std::endl;
    return 1;
  }

  json j;
  f >> j;

  BallisticsInput input{.drone_x = j["drone"]["x"].get<double>(),
                        .drone_y = j["drone"]["y"].get<double>(),
                        .drone_z = j["drone"]["z"].get<double>(),
                        .target_x = j["target"]["x"].get<double>(),
                        .target_y = j["target"]["y"].get<double>(),
                        .attack_speed = j["attack_speed"].get<double>(),
                        .ammo_name = j["ammo"].get<std::string>()};

  DropSolution sol = compute_drop_solution(input);

  std::cout << "Valid: " << (sol.valid ? "Yes" : "No") << "\n";
  std::cout << "Fire point: (" << sol.fire_x << ", " << sol.fire_y << ")\n";
  std::cout << "Time to impact: " << sol.time_to_impact << " s\n";
  std::cout << "Message: " << sol.message << "\n";

  return sol.valid ? 0 : 1;
}