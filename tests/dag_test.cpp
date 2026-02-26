/**
 * @file dag_test.cpp
 * @brief Unit tests for the core::Dag class.
 * @version 1.0.0
 *
 * This file contains tests for the Directed Acyclic Graph implementation,
 * focusing on task addition, dependency validation, and cycle detection.
 */

#include "dagra/core/dag.hpp"
#include <gtest/gtest.h>

/**
 * @brief Tests that a task can be added to the DAG and retrieved.
 */
TEST(DagTest, AddAndGetTask) {
    dagra::core::Dag dag;
    dagra::core::Task task{"task-1", "echo 'test'", {}};
    dag.add_task(task);

    const auto& retrieved_task = dag.get_task("task-1");
    EXPECT_EQ(retrieved_task.id, "task-1");
    EXPECT_EQ(dag.get_all_tasks().size(), 1);
}

/**
 * @brief Tests that the DAG validation successfully passes for a valid graph.
 */
TEST(DagTest, ValidationSuccess) {
    dagra::core::Dag dag;
    dag.add_task({"task-1", "cmd", {}});
    dag.add_task({"task-2", "cmd", {"task-1"}});
    
    EXPECT_NO_THROW(dag.validate());
}

/**
 * @brief Tests that DAG validation throws an error for a dependency on an unknown task.
 */
TEST(DagTest, ValidationFailsWithMissingDependency) {
    dagra::core::Dag dag;
    dag.add_task({"task-1", "cmd", {"nonexistent-task"}});

    EXPECT_THROW(dag.validate(), std::runtime_error);
}

/**
 * @brief Tests that DAG validation throws an error when a simple cycle is detected.
 */
TEST(DagTest, ValidationFailsWithSimpleCycle) {
    dagra::core::Dag dag;
    dag.add_task({"task-1", "cmd", {"task-2"}});
    dag.add_task({"task-2", "cmd", {"task-1"}});

    EXPECT_THROW(dag.validate(), std::runtime_error);
}

/**
 * @brief Tests that DAG validation throws an error when a more complex, transitive cycle is detected.
 */
TEST(DagTest, ValidationFailsWithTransitiveCycle) {
    dagra::core::Dag dag;
    dag.add_task({"task-1", "cmd", {"task-3"}});
    dag.add_task({"task-2", "cmd", {"task-1"}});
    dag.add_task({"task-3", "cmd", {"task-2"}});

    EXPECT_THROW(dag.validate(), std::runtime_error);
}

/**
 * @brief Tests that attempting to get a non-existent task throws an error.
 */
TEST(DagTest, GetNonExistentTask) {
    dagra::core::Dag dag;
    EXPECT_THROW(dag.get_task("nonexistent"), std::runtime_error);
}
