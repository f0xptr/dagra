/**
 * @file runner_test.cpp
 * @brief Unit tests for the execution::Runner class.
 * @version 1.0.0
 *
 * This file contains tests for the task execution runner, specifically focusing
 * on the dry-run functionality to ensure it correctly simulates task execution
 * order without actually running commands.
 */

#include "dagra/execution/runner.hpp"
#include "dagra/core/dag.hpp"
#include "dagra/utils/logger.hpp" // For Logger to redirect output if needed
#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Test fixture for Runner tests
class RunnerTest : public ::testing::Test {
protected:
    dagra::core::Dag dag;
    // Store original cout and cerr buffers
    std::streambuf* old_cout_buf = nullptr;
    std::streambuf* old_cerr_buf = nullptr;
    // Stringstream to capture output
    std::stringstream captured_output;

    void SetUp() override {
        // Add some tasks for testing a linear dependency chain
        dag.add_task({"task-a", "echo A", {}});
        dag.add_task({"task-b", "echo B", {"task-a"}});
        dag.add_task({"task-c", "echo C", {"task-b"}});

        // Redirect std::cout to our stringstream
        old_cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(captured_output.rdbuf());
        
        // Redirect std::cerr to our stringstream
        old_cerr_buf = std::cerr.rdbuf();
        std::cerr.rdbuf(captured_output.rdbuf());
    }

    void TearDown() override {
        // Restore std::cout
        std::cout.rdbuf(old_cout_buf);
        // Restore std::cerr
        std::cerr.rdbuf(old_cerr_buf);
    }
};

/**
 * @brief Tests that the dry-run mode correctly prints the execution plan.
 *
 * This test verifies that when the runner is in dry-run mode, it outputs
 * messages indicating the planned execution order of tasks without
 * actually executing their commands.
 */
TEST_F(RunnerTest, DryRunPrintsExecutionPlan) {
    dagra::execution::Runner runner(dag, true); // dry_run = true
    runner.execute_all();

    std::string output = captured_output.str();
    
    // Check for expected dry-run messages and task IDs in the output
    EXPECT_NE(output.find("[DRY-RUN] Starting dry run."), std::string::npos);
    EXPECT_NE(output.find("Execute Task 'task-a' (Command: echo A)"), std::string::npos);
    EXPECT_NE(output.find("Execute Task 'task-b' (Command: echo B)"), std::string::npos);
    EXPECT_NE(output.find("Execute Task 'task-c' (Command: echo C)"), std::string::npos);
    EXPECT_NE(output.find("[DRY-RUN] Dry run finished."), std::string::npos);
    
    // Verify the order of execution for the linear dependency chain
    ASSERT_LT(output.find("Execute Task 'task-a'"), output.find("Execute Task 'task-b'"));
    ASSERT_LT(output.find("Execute Task 'task-b'"), output.find("Execute Task 'task-c'"));
}

/**
 * @brief Tests that dry-run mode identifies and reports deadlocks.
 *
 * This test creates a cyclic dependency to ensure that the dry-run mode
 * correctly detects and reports deadlocks, listing the tasks involved.
 */
TEST_F(RunnerTest, DryRunDetectsDeadlock) {
    // Clear previous tasks and set up a cycle
    dagra::core::Dag cyclic_dag;
    cyclic_dag.add_task({"t1", "cmd1", {"t2"}});
    cyclic_dag.add_task({"t2", "cmd2", {"t1"}});

    dagra::execution::Runner runner(cyclic_dag, true); // dry_run = true
    runner.execute_all();

    std::string output = captured_output.str();
    
    // Check for deadlock detection message and involved tasks
    EXPECT_NE(output.find("[ERROR]   Deadlock detected in dry run."), std::string::npos);
    EXPECT_NE(output.find("- Task: t1"), std::string::npos);
    EXPECT_NE(output.find("- Task: t2"), std::string::npos);
}
