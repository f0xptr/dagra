/**
 * @file task.hpp
 * @brief Defines the core Task structure for the Directed Acyclic Graph.
 * @version 1.0.0
 *
 * This file contains the definition of the `Task` struct, which is the
 * fundamental unit of work in the Dagra application. Each task has a unique
 * identifier, a shell command to execute, and a list of dependencies on other
 * tasks.
 */

#pragma once

#include <string>
#include <vector>

namespace dagra::core {

    /**
     * @struct Task
     * @brief Represents a single unit of work in the DAG.
     *
     * A Task is defined by its ID, the command it executes, and the IDs of
     * any other tasks that must be completed before this one can start.
     */
    struct Task {
        /// @brief A unique identifier for the task (e.g., "build", "test").
        std::string id;
        
        /// @brief The shell command to be executed for this task.
        std::string command;
        
        /// @brief A list of task IDs that this task depends on.
        std::vector<std::string> dependencies;
    };

} // namespace dagra::core
