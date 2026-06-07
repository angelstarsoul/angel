cmake_minimum_required(VERSION 3.20)

add_library(ballistics STATIC src/ballistics.cpp)

target_include_directories(ballistics PUBLIC include)
target_compile_features(ballistics PUBLIC cxx_std_20)

add_executable(ballistics_cli src/main.cpp)

target_link_libraries(ballistics_cli PRIVATE ballistics)


if(NOT CMAKE_CROSSCOMPILING)
    include(FetchContent)
    FetchContent_Declare(
        googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
                       DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    add_executable(ballistics_tests tests/ballistics_tests.cpp)
    target_link_libraries(ballistics_tests PRIVATE ballistics GTest::gtest_main)

    # Явна реєстрація тесту (щоб ctest бачив всі тести)
    add_test(NAME BallisticsTest COMMAND ballistics_tests)
endif()
