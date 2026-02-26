/**
 * @file parser.hpp
 * @brief Defines the command-line argument parser and YAML configuration loader.
 * @version 1.0.0
 *
 * This file declares the `Parser` class, which is responsible for interpreting
 * command-line arguments and parsing the user-provided YAML file that defines
 * the tasks for Dagra to execute.
 */

#pragma once

#include "dagra/core/task.hpp"
#include <string>
#include <vector>

namespace dagra::cli {

    /**
     * @struct AppOptions
     * @brief Holds the application's configuration parsed from command-line arguments.
     *
     * This includes the path to the main configuration file and any operational
     * flags, such as whether to perform a dry run.
     */
    struct AppOptions {
        std::string config_filepath;
        bool dry_run = false;
    };

    /**
     * @class Parser
     * @brief A utility class for parsing command-line arguments and YAML files.
     */
    class Parser {
    public:
        /**
         * @brief Parses command-line arguments to extract the configuration file path
         *        and operational flags.
         * @param argc The number of command-line arguments.
         * @param argv An array of command-line argument strings.
         * @return An AppOptions struct containing the parsed options.
         * @throw std::runtime_error If the configuration file path is not provided.
         */
        static AppOptions parse_args(int argc, char* argv[]);

        /**
         * @brief Parses a YAML file to extract a list of tasks.
         * @param filepath The absolute or relative path to the YAML configuration file.
         * @return A vector of Task objects defined in the file.
         * @throw std::runtime_error If the file is invalid or cannot be opened.
         */
        static std::vector<core::Task> parse_yaml(const std::string& filepath);
    };

} // namespace dagra::cli
