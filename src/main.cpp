/**
 * @file main.cpp
 * @brief The entry point for the Dagra CLI tool.
 * @version 1.0.0
 *
 * This file contains the main function that orchestrates the entire Dagra
 * application lifecycle. It parses command-line arguments, loads tasks from
 * a configuration file, builds a dependency graph, and triggers the execution.
 */

#include "dagra/cli/parser.hpp"
#include "dagra/core/dag.hpp"
#include "dagra/execution/runner.hpp"
#include "dagra/utils/logger.hpp"
#include <exception>

/**
 * @brief The main entry point of the Dagra application.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return Returns 0 on successful execution, 1 on failure.
 */
int main(int argc, char* argv[]) {
    try {
        dagra::cli::AppOptions options = dagra::cli::Parser::parse_args(argc, argv);
        
        if (options.dry_run) {
            dagra::utils::Logger::info("Dagra running in dry-run mode.");
        }
        
        dagra::utils::Logger::info("Target config: " + options.config_filepath);
        dagra::utils::Logger::info("Parsing configuration file...");
        auto tasks = dagra::cli::Parser::parse_yaml(options.config_filepath);

        dagra::utils::Logger::info("Building dependency graph...");
        dagra::core::Dag dag;
        for (const auto& task : tasks) {
            dag.add_task(task);
        }

        dagra::utils::Logger::info("Validating dependency graph...");
        dag.validate();

        dagra::utils::Logger::info("Initializing execution engine...");
        dagra::execution::Runner runner(dag, options.dry_run);
        runner.execute_all();

        if (!options.dry_run) {
            dagra::utils::Logger::success("All tasks completed successfully. Dagra finished.");
        }

    } catch (const std::exception& e) {
        dagra::utils::Logger::error(std::string("Fatal error: ") + e.what());
        return 1;
    }

    return 0;
}
