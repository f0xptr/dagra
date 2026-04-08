/**
 * @file task.hpp
 * @brief Defines the core Task structure for the Directed Acyclic Graph.
 * @version 1.1.0
 *
 * This file contains the definition of the `Task` struct, which is the
 * fundamental unit of work in the Dagra application. Each task has a unique
 * identifier, a shell command to execute, a list of dependencies on other
 * tasks, an optional timeout, and optional environment variables.
 */

#pragma once

#include <string>
#include <vector>

namespace dagra::core {

    /**
     * @struct Task
     * @brief Represents a single unit of work in the DAG.
     *
     * A Task is defined by its ID, the command it executes, the IDs of
     * any other tasks that must be completed before this one can start,
     * an optional timeout in seconds, and optional environment variables.
     */
    struct Task {
        /// @brief A unique identifier for the task (e.g., "build", "test").
        std::string id;
        
        /// @brief The shell command to be executed for this task.
        std::string command;
        
        /// @brief A list of task IDs that this task depends on.
        std::vector<std::string> dependencies;
        
        /// @brief Timeout for task execution in seconds (0 = unlimited).
        int timeout_seconds = 0;
        
        /// @brief Environment variables for this task (format: "KEY=value").
        std::vector<std::string> env_vars;
    };

} // namespace dagra::core
