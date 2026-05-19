#include "ballistics.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "Usage: ballistics_cli <input_file>\n";
    return 1;
  }


  std::cout << "=== Ballistics Calculator ===\n";
  std::cout << "Input file: " << argv[1] << "\n";


  BallisticsInput input{.drone_x = 100.0,
                        .drone_y = 100.0,
                        .drone_z = 100.0,
                        .target_x = 200.0,
                        .target_y = 200.0,
                        .attack_speed = 10.0,
                        .ammo_name = "VOG-17"};

  DropSolution sol = compute_drop_solution(input);

  std::cout << "Valid: " << (sol.valid ? "Yes" : "No") << "\n";
  std::cout << "Fire point: (" << sol.fire_x << ", " << sol.fire_y << ")\n";
  std::cout << "Time to impact: " << sol.time_to_impact << " s\n";
  std::cout << "Message: " << sol.message << "\n";

  return sol.valid ? 0 : 1;
}