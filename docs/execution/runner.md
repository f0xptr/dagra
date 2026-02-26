# Execution Module

The `execution` module is the engine of Dagra. It takes a validated Directed Acyclic Graph (DAG) and executes the tasks in the correct order, leveraging parallelism to improve performance.

## Runner Class

**File:** `include/dagra/execution/runner.hpp`

The `Runner` class is responsible for orchestrating the execution of the tasks in the DAG.

### Constructor

-   `explicit Runner(const core::Dag& dag, bool dry_run = false)`: The constructor takes the validated `Dag` and an optional `dry_run` flag.
    -   `dag`: A constant reference to the task graph.
    -   `dry_run`: If `true`, the runner will simulate the execution without running any actual commands.

### `execute_all()`

This is the main method of the `Runner`. It manages the entire execution lifecycle.

#### Normal Execution (`dry_run` is `false`)

1.  **Task Scheduling**: The runner continuously scans the list of all tasks to find those that are ready to run. A task is considered "ready" if all of its dependencies have been successfully completed.

2.  **Parallel Execution**: Each ready task is launched in a separate thread (`std::thread`). This allows multiple tasks with no direct dependency on each other to run in parallel.

3.  **State Tracking**: The runner maintains several internal states for each task:
    -   `completed`: A set of task IDs that have finished successfully.
    -   `running`: A set of task IDs that are currently executing.

4.  **Synchronization**: The runner uses a `std::mutex` and `std::condition_variable` to manage concurrency and to wait efficiently for tasks to complete before scheduling new ones.

5.  **Error Handling**: If a task's command returns a non-zero exit code, it is marked as "failed". The runner will halt all further execution and throw a `std::runtime_error` to signal the failure. It also detects and reports deadlocks if the execution gets into a state where no tasks are running but not all tasks are complete.

#### Dry Run Mode (`dry_run` is `true`)

If the `dry_run` flag is set, the `execute_all()` method will perform a simulation of the execution:

-   It determines a valid execution order by topologically sorting the tasks.
-   It prints the tasks in the order they would be executed, without running any commands.
-   This is useful for debugging and verifying the correctness of a configuration file before running it.
-   It will also detect and report deadlocks if the graph has a cycle.
