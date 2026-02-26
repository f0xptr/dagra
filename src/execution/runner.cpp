/**
 * @file runner.cpp
 * @brief Implements the parallel task execution engine.
 * @version 1.0.0
 *
 * This file contains the implementation for the Runner class, which is
 * responsible for executing tasks from a DAG in the correct order and in
 * parallel where possible.
 */

#include "dagra/execution/runner.hpp"
#include "dagra/utils/logger.hpp"
#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <unordered_set>
#include <vector>

namespace dagra::execution {

    /**
     * @brief Constructs a Runner.
     * @param dag The task graph to execute.
     * @param dry_run Whether to simulate or execute.
     */
    Runner::Runner(const core::Dag& dag, bool dry_run) : dag_(dag), dry_run_(dry_run) {}

    /**
     * @brief Performs a simulated run, printing the execution plan.
     *
     * This function determines a valid topological sort of the DAG and prints
     * the tasks in the order they would be executed. It does not run any actual
     * commands. It also detects circular dependencies if no task can be run.
     */
    void run_dry() {
        // This function is not implemented as the logic is within execute_all.
        // This is a placeholder for future refactoring if needed.
    }

    /**
     * @brief Executes all tasks in the DAG.
     *
     * This method orchestrates the execution. If `dry_run_` is true, it will
     * print the intended execution order without running commands. Otherwise, it
     * launches tasks in separate threads as soon as their dependencies are met.
     * The main loop waits on a condition variable and dispatches new tasks as
     * others complete.
     *
     * @throw std::runtime_error If a task fails, a deadlock is detected, or the
     *      execution is halted for any other reason.
     */
    void Runner::execute_all() {
        const auto& all_tasks = dag_.get_all_tasks();
        const size_t total_tasks = all_tasks.size();

        if (total_tasks == 0) {
            utils::Logger::info("No tasks to execute.");
            return;
        }

        if (dry_run_) {
            utils::Logger::dry_run("Starting dry run. Tasks will be listed in a possible execution order.");
            std::unordered_set<std::string> completed_dry;

            while (completed_dry.size() < total_tasks) {
                std::vector<core::Task> ready_tasks;
                for (const auto& [id, task] : all_tasks) {
                    if (completed_dry.count(id)) {
                        continue;
                    }

                    bool dependencies_met = true;
                    for (const auto& dep : task.dependencies) {
                        if (completed_dry.find(dep) == completed_dry.end()) {
                            dependencies_met = false;
                            break;
                        }
                    }

                    if (dependencies_met) {
                        ready_tasks.push_back(task);
                    }
                }

                if (ready_tasks.empty()) {
                    if (completed_dry.size() < total_tasks) {
                        utils::Logger::error("Deadlock detected in dry run. The following tasks form a cycle or have missing dependencies:");
                        for (const auto& [id, task] : all_tasks) {
                            if(completed_dry.find(id) == completed_dry.end()) {
                                utils::Logger::error(" - Task: " + id);
                            }
                        }
                    }
                    break;
                }

                for (const auto& task : ready_tasks) {
                    utils::Logger::dry_run("Execute Task '" + task.id + "' (Command: " + task.command + ")");
                    completed_dry.insert(task.id);
                }
            }
            utils::Logger::dry_run("Dry run finished.");
            return;
        }

        std::mutex mtx;
        std::condition_variable cv;
        std::unordered_set<std::string> completed;
        std::unordered_set<std::string> running;
        std::atomic<bool> has_error = false;

        while (completed.size() < total_tasks && !has_error) {
            std::vector<core::Task> ready_to_start;
            
            {
                std::unique_lock<std::mutex> lock(mtx);
                for (const auto& [id, task] : all_tasks) {
                    if (completed.count(id) || running.count(id)) {
                        continue;
                    }

                    bool can_run = true;
                    for (const auto& dep : task.dependencies) {
                        if (completed.find(dep) == completed.end()) {
                            can_run = false;
                            break;
                        }
                    }

                    if (can_run) {
                        ready_to_start.push_back(task);
                        running.insert(id);
                    }
                }

                if (ready_to_start.empty() && running.empty() && completed.size() < total_tasks) {
                    utils::Logger::error("Deadlock detected! No tasks can be started.");
                    has_error = true;
                    break;
                }
            }

            for (const auto& task : ready_to_start) {
                std::thread([&, task]() {
                    utils::Logger::info("Running: [" + task.id + "] -> " + task.command);
                    int result = std::system(task.command.c_str());

                    std::lock_guard<std::mutex> lock(mtx);
                    running.erase(task.id);

                    if (result == 0) {
                        completed.insert(task.id);
                        utils::Logger::success("Success: [" + task.id + "]");
                    } else {
                        utils::Logger::error("Failed: [" + task.id + "] (Exit code: " + std::to_string(result) + ")");
                        has_error = true;
                    }
                    
                    cv.notify_one();
                }).detach();
            }

            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]() {
                // Wait if there is no error, and there are still tasks running or no tasks are ready to be processed yet.
                return has_error.load() || (running.empty() && completed.size() < total_tasks) || completed.size() == total_tasks;
            });
        }

        if (has_error) {
            throw std::runtime_error("Execution halted due to task failure or deadlock.");
        }
    }

} // namespace dagra::execution
