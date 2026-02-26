#
# CMake build configuration for the Dagra project.
# Version: 1.0.0
#
# This file governs how the project is built, including its dependencies,
# source files, and test suite configuration.
#

# Set the minimum required version of CMake and define the project.
cmake_minimum_required(VERSION 3.17)
project(Dagra VERSION 1.0.0 LANGUAGES CXX)

# Set the C++ standard to C++17 and enforce it.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compiler warnings for better code quality.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O3")

# Include the FetchContent module to manage external dependencies.
include(FetchContent)

# Declare the yaml-cpp dependency from its GitHub repository.
# We pin it to a specific tag to ensure the build is reproducible.
message(STATUS "Fetching yaml-cpp...")
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.9.0
)
# Disable yaml-cpp's tests and tools to speed up our build, as we only need the library.
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(yaml-cpp)

# Find the threads library, which is required for our application.
find_package(Threads REQUIRED)

# To build our library objects, we need to collect all source files.
# However, the main function should not be part of the library.
set(DAGRA_SOURCES
    src/cli/parser.cpp
    src/core/dag.cpp
    src/execution/runner.cpp
)

# Add a library for the core logic. This allows it to be reused for the main executable and tests.
add_library(dagra_core ${DAGRA_SOURCES})
target_include_directories(dagra_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(dagra_core PRIVATE Threads::Threads yaml-cpp)

# Define the main executable for the application.
add_executable(dagra src/main.cpp)
target_link_libraries(dagra PRIVATE dagra_core)


#
# Testing Configuration
#
# The following section sets up the testing environment using GoogleTest.
# It will be enabled if the `dagra_build_tests` option is ON.
#
option(DAGRA_BUILD_TESTS "Build the test suite" ON)

if(DAGRA_BUILD_TESTS)
    # Enable the CTest testing framework.
    enable_testing()
    
    # Fetch the GoogleTest framework.
    message(STATUS "Fetching GoogleTest...")
    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG release-1.12.1
    )
    # Make the GoogleTest targets available.
    FetchContent_MakeAvailable(googletest)
    
    # Create the test executable.
    add_executable(dagra_tests
        tests/main.cpp
        tests/parser_test.cpp
        tests/dag_test.cpp
        tests/runner_test.cpp
    )
    
    # Link the test executable against our core library and GoogleTest.
    target_link_libraries(dagra_tests PRIVATE dagra_core gtest_main)
    
    # Include the GoogleTest module to simplify test discovery.
    include(GoogleTest)
    gtest_discover_tests(dagra_tests)
endif()
