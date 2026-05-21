cmake_minimum_required(VERSION 3.20)

# Бібліотека
add_library(ballistics STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ballistics.cpp
)

target_include_directories(ballistics PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ballistics PUBLIC cxx_std_20)

# Консольна програма
add_executable(ballistics_cli
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(ballistics_cli PRIVATE ballistics)


if(NOT CMAKE_CROSSCOMPILING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    include(GoogleTest)       
    
    add_executable(ballistics_tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/ballistics_tests.cpp
    )

    target_link_libraries(ballistics_tests PRIVATE ballistics GTest::gtest_main)
 
    
    gtest_discover_tests(ballistics_tests)
endif()
