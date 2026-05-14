cmake_minimum_required(VERSION 3.20)


add_library(telemetry STATIC
    src/telemetry.cpp
)

target_include_directories(telemetry PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(telemetry PUBLIC cxx_std_20)


add_executable(telemetry_check
    src/main.cpp
)

target_link_libraries(telemetry_check PRIVATE telemetry)


set_target_properties(telemetry_check PROPERTIES
    OUTPUT_NAME "telemetry_check"
)