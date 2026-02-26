/**
 * @file parser_test.cpp
 * @brief Unit tests for the cli::Parser class.
 * @version 1.0.0
 *
 * This file contains tests for command-line argument parsing and YAML file
 * processing to ensure they behave as expected under various conditions.
 */

#include "dagra/cli/parser.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <vector>

// Test fixture for parser tests
class ParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a dummy config file for testing YAML parsing.
        std::ofstream outfile("test_config.yaml");
        outfile << "tasks:" << std::endl;
        outfile << "  - id: task-a" << std::endl;
        outfile << "    command: 'echo A'" << std::endl;
        outfile << "  - id: task-b" << std::endl;
        outfile << "    command: 'echo B'" << std::endl;
        outfile << "    depends_on:" << std::endl;
        outfile << "      - task-a" << std::endl;
        outfile.close();
    }

    void TearDown() override {
        std::remove("test_config.yaml");
    }
};

/**
 * @brief Tests the parsing of basic command-line arguments.
 */
TEST_F(ParserTest, ParseArgsBasic) {
    char* argv[] = {(char*)"dagra", (char*)"config.yaml", nullptr};
    int argc = 2;

    auto options = dagra::cli::Parser::parse_args(argc, argv);
    EXPECT_EQ(options.config_filepath, "config.yaml");
    EXPECT_FALSE(options.dry_run);
}

/**
 * @brief Tests the parsing of the --dry-run flag.
 */
TEST_F(ParserTest, ParseArgsDryRun) {
    char* argv[] = {(char*)"dagra", (char*)"config.yaml", (char*)"--dry-run", nullptr};
    int argc = 3;

    auto options = dagra::cli::Parser::parse_args(argc, argv);
    EXPECT_EQ(options.config_filepath, "config.yaml");
    EXPECT_TRUE(options.dry_run);
}

/**
 * @brief Tests that argument parsing throws an error if no config file is given.
 */
TEST_F(ParserTest, ParseArgsMissingFile) {
    char* argv[] = {(char*)"dagra", nullptr};
    int argc = 1;
    EXPECT_THROW(dagra::cli::Parser::parse_args(argc, argv), std::runtime_error);
}

/**
 * @brief Tests successful parsing of a valid YAML file.
 */
TEST_F(ParserTest, ParseYamlSuccess) {
    auto tasks = dagra::cli::Parser::parse_yaml("test_config.yaml");
    ASSERT_EQ(tasks.size(), 2);

    EXPECT_EQ(tasks[0].id, "task-a");
    EXPECT_EQ(tasks[0].command, "echo A");
    EXPECT_TRUE(tasks[0].dependencies.empty());

    EXPECT_EQ(tasks[1].id, "task-b");
    EXPECT_EQ(tasks[1].command, "echo B");
    ASSERT_EQ(tasks[1].dependencies.size(), 1);
    EXPECT_EQ(tasks[1].dependencies[0], "task-a");
}

/**
 * @brief Tests that YAML parsing throws an error for a non-existent file.
 */
TEST_F(ParserTest, ParseYamlFileNotExist) {
    EXPECT_THROW(dagra::cli::Parser::parse_yaml("nonexistent.yaml"), std::runtime_error);
}
