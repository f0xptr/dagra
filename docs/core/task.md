# Core Module: Task

The `Task` is the most fundamental data structure in Dagra. It represents a single unit of work that needs to be executed.

## Task Struct

**File:** `include/dagra/core/task.hpp`

The `Task` struct contains all the information needed to define a task and its position within the dependency graph.

### Fields

-   `id` (std::string): A unique identifier for the task. This ID is used to reference the task in the dependency lists of other tasks.
-   `command` (std::string): The shell command that will be executed when the task is run.
-   `dependencies` (std::vector<std::string>): A list of task IDs that must be completed before this task can be executed. If a task has no dependencies, this vector will be empty.

## YAML Representation

In the YAML configuration file, a task is represented as a mapping with the following keys:

-   `id`: The task's unique ID.
-   `command`: The command to run.
-   `depends_on` (optional): A list of dependency IDs.

### Example

Here is an example of how a `Task` is defined in the `config.yaml`:

```yaml
tasks:
  - id: build
    command: "g++ -o my_app main.cpp"
    depends_on: []

  - id: test
    command: "./my_app_tests"
    depends_on:
      - build
```

In this example:
- The `build` task has the ID "build" and a compile command. It has no dependencies.
- The `test` task has the ID "test" and depends on the `build` task. This means the `test` task will only be executed after the `build` task has completed successfully.
