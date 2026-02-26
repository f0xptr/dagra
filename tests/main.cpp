/**
 * @file main.cpp
 * @brief The main entry point for the Dagra test suite.
 * @version 1.0.0
 *
 * This file contains the main function that initializes and runs the GoogleTest
 * framework, executing all discovered unit tests.
 */

#include <gtest/gtest.h>

/**
 * @brief The main function for the test executable.
 *
 * Initializes the GoogleTest framework and runs all registered tests.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return The result of the test run.
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
