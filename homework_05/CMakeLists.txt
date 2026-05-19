cmake_minimum_required(VERSION 3.20)


add_library(telemetry STATIC
    src/telemetry.cpp
)

target_include_directories(telemetry PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(telemetry PUBLIC cxx_std_20)


add_executable(homework_05
    src/main.cpp
)

target_link_libraries(homework_05 PRIVATE telemetry)


set_target_properties(homework_05 PROPERTIES
    OUTPUT_NAME "homework_05"
)