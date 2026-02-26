/**
 * @file dag.cpp
 * @brief Implements the Directed Acyclic Graph logic, including validation.
 * @version 1.0.0
 *
 * This file contains the implementation for the Dag class. It provides the
 * logic for adding tasks and, most importantly, for validating the graph to
 * ensure it is well-formed (i.e., contains no missing dependencies and no
 * circular references).
 */

#include "dagra/core/dag.hpp"
#include "dagra/utils/logger.hpp"
#include <stdexcept>
#include <unordered_set>

namespace dagra::core {

    /**
     * @brief Adds a task to the DAG.
     * @param task The task to be added.
     */
    void Dag::add_task(const Task& task) {
        tasks_[task.id] = task;
    }

    /**
     * @brief Retrieves a task by its ID.
     * @param id The ID of the task to find.
     * @return A const reference to the task.
     */
    const Task& Dag::get_task(const std::string& id) const {
        auto it = tasks_.find(id);
        if (it == tasks_.end()) {
            throw std::runtime_error("Task with ID '" + id + "' not found in the DAG.");
        }
        return it->second;
    }

    /**
     * @brief Returns all tasks in the DAG.
     * @return A const reference to the map of tasks.
     */
    const std::unordered_map<std::string, Task>& Dag::get_all_tasks() const {
        return tasks_;
    }

    /**
     * @brief Validates the DAG for missing dependencies and cycles.
     * @throw std::runtime_error if validation fails.
     */
    void Dag::validate() const {
        std::unordered_set<std::string> visited;
        std::unordered_set<std::string> recursion_stack;

        // 1. Check for missing dependencies and cycles.
        for (const auto& [id, task] : tasks_) {
            for (const auto& dep : task.dependencies) {
                if (tasks_.find(dep) == tasks_.end()) {
                    throw std::runtime_error("Validation failed: Task '" + id + "' has an unknown dependency '" + dep + "'.");
                }
            }
            if (visited.find(id) == visited.end()) {
                detect_cycle_util(id, visited, recursion_stack);
            }
        }

        utils::Logger::info("DAG validated successfully. No missing dependencies or cycles found.");
    }

    /**
     * @brief A recursive utility to detect cycles using DFS.
     * @param task_id The current task ID to visit.
     * @param visited A set of all visited nodes so far.
     * @param recursion_stack A set of nodes in the current recursion path.
     * @throw std::runtime_error if a cycle is detected.
     */
    void Dag::detect_cycle_util(const std::string& task_id, std::unordered_set<std::string>& visited, std::unordered_set<std::string>& recursion_stack) const {
        visited.insert(task_id);
        recursion_stack.insert(task_id);

        const auto& task = get_task(task_id);
        for (const auto& dep_id : task.dependencies) {
            if (recursion_stack.count(dep_id)) {
                throw std::runtime_error("Cycle detected in dependency graph involving task '" + dep_id + "'.");
            }
            if (visited.find(dep_id) == visited.end()) {
                detect_cycle_util(dep_id, visited, recursion_stack);
            }
        }

        recursion_stack.erase(task_id);
    }

} // namespace dagra::core
