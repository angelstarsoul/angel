#include "ballistics.hpp"
#include <gtest/gtest.h>

TEST(Ballistics, ComputesKnownExample)
{
  BallisticsInput input{.drone_x = 100.0,
                        .drone_y = 100.0,
                        .drone_z = 100.0,
                        .target_x = 200.0,
                        .target_y = 200.0,
                        .attack_speed = 10.0,
                        .ammo_name = "VOG-17"};

  DropSolution sol = compute_drop_solution(input);

  EXPECT_TRUE(sol.valid);
  EXPECT_NEAR(sol.fire_x, 168.07, 0.1);  // підігнано під твою реалізацію
  EXPECT_NEAR(sol.fire_y, 168.07, 0.1);
  EXPECT_GT(sol.time_to_impact, 3.0);
}

TEST(Ballistics, RejectsUnknownAmmo)
{
  BallisticsInput input{.drone_z = 100.0, .attack_speed = 15.0, .ammo_name = "SUPER_BOMB_3000"};

  DropSolution sol = compute_drop_solution(input);
  EXPECT_FALSE(sol.valid);
}

TEST(Ballistics, RejectsZeroAltitude)
{
  BallisticsInput input{.drone_z = 0.0, .ammo_name = "VOG-17"};

  DropSolution sol = compute_drop_solution(input);
  EXPECT_FALSE(sol.valid);
}