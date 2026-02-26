/**
 * @file runner.hpp
 * @brief Declares the class for managing parallel execution of tasks.
 * @version 1.0.0
 *
 * This file contains the declaration of the `Runner` class, which takes a
 * Directed Acyclic Graph (DAG) of tasks and executes them in parallel according
 * to their dependencies. It also supports a "dry run" mode to preview the
 * execution plan without running any commands.
 */

#pragma once

#include "dagra/core/dag.hpp"

namespace dagra::execution {

    /**
     * @class Runner
     * @brief Manages the execution of a task DAG.
     *
     * The Runner is responsible for traversing the DAG and executing tasks
     * as their dependencies are met. It uses a thread pool to run tasks in
     * parallel and ensures that the entire process is thread-safe.
     */
    class Runner {
    public:
        /**
         * @brief Constructs a new Runner.
         * @param dag The validated Directed Acyclic Graph of tasks to execute.
         * @param dry_run If true, the runner will only simulate the execution.
         */
        explicit Runner(const core::Dag& dag, bool dry_run = false);

        /**
         * @brief Executes all tasks in the DAG.
         *
         * If in normal mode, this method will execute all tasks in parallel,
         * respecting their dependencies. If in dry run mode, it will print the
         * execution plan without running any commands.
         *
         * @throw std::runtime_error If a task fails or a deadlock is detected.
         */
        void execute_all();

    private:
        const core::Dag& dag_;
        const bool dry_run_;
    };

} // namespace dagra::execution
