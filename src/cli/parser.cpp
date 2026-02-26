/**
 * @file parser.cpp
 * @brief Implements the command-line argument and YAML configuration parser.
 * @version 1.0.0
 *
 * This file contains the implementation for the Parser class, which handles
 * both command-line flags and the parsing of YAML task definition files.
 */

#include "dagra/cli/parser.hpp"
#include <stdexcept>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace dagra::cli {

    /**
     * @brief Parses command-line arguments to extract options.
     *
     * Iterates through the command-line arguments to find the configuration
     * file path and the `--dry-run` flag.
     *
     * @param argc The argument count.
     * @param argv The argument vector.
     * @return An AppOptions struct populated with the found settings.
     */
    AppOptions Parser::parse_args(int argc, char* argv[]) {
        if (argc < 2) {
            throw std::runtime_error("Usage: dagra <config.yaml> [--dry-run]");
        }

        AppOptions options;
        std::vector<std::string> args(argv + 1, argv + argc);

        bool config_found = false;
        for (const auto& arg : args) {
            if (arg == "--dry-run") {
                options.dry_run = true;
            } else if (!config_found && !arg.empty() && arg.rfind("--", 0) != 0) {
                // Treat the first non-flag argument as the config file path.
                options.config_filepath = arg;
                config_found = true;
            }
        }

        if (options.config_filepath.empty()) {
            throw std::runtime_error("Configuration file path is missing. Usage: dagra <config.yaml> [--dry-run]");
        }

        return options;
    }

    /**
     * @brief Parses a YAML file to create a list of tasks.
     *
     * Loads a YAML file from the given path and validates its structure. It expects
     * a top-level `tasks` sequence, where each item defines a task with at least
     * an `id` and a `command`.
     *
     * @param filepath The path to the YAML configuration file.
     * @return A vector of tasks.
     * @throw std::runtime_error If the file format is invalid or a task is malformed.
     * @throw YAML::Exception If the file cannot be parsed.
     */
    std::vector<core::Task> Parser::parse_yaml(const std::string& filepath) {
        std::vector<core::Task> parsed_tasks;

        try {
            YAML::Node config = YAML::LoadFile(filepath);

            if (!config["tasks"] || !config["tasks"].IsSequence()) {
                throw std::runtime_error("Invalid YAML: The 'tasks' sequence is missing or not a sequence.");
            }

            for (const auto& node : config["tasks"]) {
                if (!node["id"] || !node["command"]) {
                    throw std::runtime_error("Invalid YAML: A task is missing the required 'id' or 'command' field.");
                }

                core::Task task;
                task.id = node["id"].as<std::string>();
                task.command = node["command"].as<std::string>();

                if (node["depends_on"] && node["depends_on"].IsSequence()) {
                    for (const auto& dep : node["depends_on"]) {
                        task.dependencies.push_back(dep.as<std::string>());
                    }
                }
                parsed_tasks.push_back(task);
            }
        } catch (const YAML::Exception& e) {
            // Re-throw with a more descriptive error message.
            throw std::runtime_error("Failed to parse YAML file '" + filepath + "': " + e.what());
        }

        return parsed_tasks;
    }

} // namespace dagra::cli
