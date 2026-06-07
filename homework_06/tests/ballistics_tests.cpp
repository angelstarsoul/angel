#include "ballistics.hpp"
#include <gtest/gtest.h>

TEST(BallisticsTest, ComputesKnownExample) {
    BallisticsInput input{
        .drone_x = 100.0,
        .drone_y = 100.0,
        .drone_z = 100.0,
        .target_x = 200.0,
        .target_y = 200.0,
        .attack_speed = 15.0,
        .ammo_name = "VOG-17"
    };

    DropSolution sol = compute_drop_solution(input);

    EXPECT_TRUE(sol.valid);
    EXPECT_GT(sol.fire_x, 150.0);
    EXPECT_GT(sol.fire_y, 150.0);
    EXPECT_GT(sol.time_to_impact, 3.0);
    EXPECT_LT(sol.time_to_impact, 10.0);
}

TEST(BallisticsTest, InvalidAltitude) {
    BallisticsInput input{ .drone_z = -10.0, .ammo_name = "VOG-17" };
    DropSolution sol = compute_drop_solution(input);
    EXPECT_FALSE(sol.valid);
}

TEST(BallisticsTest, UnknownAmmo) {
    BallisticsInput input{ .ammo_name = "UNKNOWN" };
    DropSolution sol = compute_drop_solution(input);
    EXPECT_FALSE(sol.valid);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}