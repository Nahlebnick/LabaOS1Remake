cmake_minimum_required(VERSION 3.24)

project(Laba1OS VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)
add_subdirectory(libs)
add_subdirectory(apps)