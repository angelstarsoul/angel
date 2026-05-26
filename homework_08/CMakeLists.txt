cmake_minimum_required(VERSION 3.20)

add_library(ballistics_hw08 STATIC
    src/MissionProcessor.cpp
    src/ballistics/AnalyticalSolver.cpp
    src/config/FileConfigLoader.cpp
    src/providers/JsonTargetProvider.cpp
)

target_include_directories(ballistics_hw08 PUBLIC 
    include
    include/external
)

target_compile_features(ballistics_hw08 PUBLIC cxx_std_20)

add_executable(ballistics_cli_hw08
    src/main.cpp
)

target_link_libraries(ballistics_cli_hw08 PRIVATE ballistics_hw08)

set_target_properties(ballistics_cli_hw08 PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME "ballistics_cli_hw08"
)