# Core Module: DAG

The `Dag` (Directed Acyclic Graph) is the central data structure in Dagra. It is responsible for storing all the tasks and their inter-dependencies, and for validating the integrity of the graph.

## Dag Class

**File:** `include/dagra/core/dag.hpp`

The `Dag` class manages the collection of tasks and provides methods to ensure the graph is valid and runnable.

### Methods

-   `void add_task(const Task& task)`: Adds a new task to the graph. The tasks are stored in an internal map, using the task's `id` as the key for efficient lookup.

-   `const Task& get_task(const std::string& id) const`: Retrieves a constant reference to a task by its ID. Throws a `std::runtime_error` if the task is not found.

-   `const std::unordered_map<std::string, Task>& get_all_tasks() const`: Returns a constant reference to the internal map of all tasks in the graph.

-   `void validate() const`: This is a crucial method that checks the integrity of the DAG. It performs two main validations:
    1.  **Missing Dependencies**: It ensures that every dependency listed in every task corresponds to an actual task that exists in the graph.
    2.  **Cycle Detection**: It performs a depth-first search (DFS) to detect any circular dependencies. A cycle would make the graph un-runnable, as there would be a set of tasks that could never have their dependencies met.

    If either of these checks fails, the method throws a `std::runtime_error` with a descriptive message.

## How It Works

The `Dag` is built by parsing the YAML configuration file. Each task defined in the file is added to the `Dag` instance. Before the execution starts, the `validate()` method is called to ensure the graph is in a runnable state.

This pre-execution validation is critical for failing fast and providing clear feedback to the user if the configuration is invalid.
