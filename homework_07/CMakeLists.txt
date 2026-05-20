cmake_minimum_required(VERSION 3.20)

add_library(homework07 STATIC
    src/FileConfigLoader.cpp
    src/JsonTargetProvider.cpp
    src/AnalyticalSolver.cpp
    src/MissionProcessor.cpp
    src/Factory.cpp         
)

target_include_directories(homework07 PUBLIC 
    include 
    include/external
)

add_executable(homework07_main
    src/main.cpp
)

target_link_libraries(homework07_main PRIVATE homework07)

set_target_properties(homework07_main PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME "homework07"
)