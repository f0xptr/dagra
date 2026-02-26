/**
 * @file dag.hpp
 * @brief Declares the class for constructing and validating the Directed Acyclic Graph.
 * @version 1.0.0
 *
 * This file contains the declaration of the `Dag` class, which is responsible
 * for storing tasks and their relationships, as well as for validating the
 * integrity of the graph (e.g., checking for missing dependencies and cycles).
 */

#pragma once

#include "task.hpp"
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace dagra::core {

    /**
     * @class Dag
     * @brief Represents a Directed Acyclic Graph of tasks.
     *
     * The Dag stores tasks using a map for quick lookup by ID. It provides
     * methods for adding tasks and for validating the graph's structure to
     * ensure it is runnable.
     */
    class Dag {
    public:
        /**
         * @brief Adds a new task to the graph.
         * @param task The task object to add. If a task with the same ID already
         *             exists, it will be overwritten.
         */
        void add_task(const Task& task);

        /**
         * @brief Retrieves a task by its ID.
         * @param id The unique identifier of the task to retrieve.
         * @return A constant reference to the found task.
         * @throw std::runtime_error If no task with the given ID is found.
         */
        const Task& get_task(const std::string& id) const;

        /**
         * @brief Retrieves all tasks stored in the graph.
         * @return A constant reference to the map of all tasks.
         */
        const std::unordered_map<std::string, Task>& get_all_tasks() const;

        /**
         * @brief Validates the integrity of the DAG.
         *
         * This method performs two critical checks:
         * 1. Ensures that all task dependencies point to existing tasks.
         * 2. Detects any circular dependencies (cycles) within the graph.
         *
         * @throw std::runtime_error If a validation check fails.
         */
        void validate() const;

    private:
        /**
         * @brief A helper function for performing depth-first search to detect cycles.
         * @param task_id The ID of the current task being visited.
         * @param visited A set of nodes that have been visited in the current DFS path.
         * @param recursion_stack A set of nodes currently in the recursion stack.
         */
        void detect_cycle_util(const std::string& task_id, 
                               std::unordered_set<std::string>& visited, 
                               std::unordered_set<std::string>& recursion_stack) const;

        std::unordered_map<std::string, Task> tasks_;
    };

} // namespace dagra::core
