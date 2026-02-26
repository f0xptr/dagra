# Dagra Documentation

Welcome to the official documentation for Dagra, a simple yet powerful task runner based on a Directed Acyclic Graph (DAG). This documentation provides a comprehensive overview of the project's architecture, components, and usage.

## Overview

Dagra is designed to execute a series of tasks with specified dependencies. It reads a YAML configuration file, builds a dependency graph, and then runs the tasks in parallel as their dependencies are met. This makes it an ideal tool for build automation, data processing pipelines, and other complex workflows.

## Key Features

- **DAG-based Execution**: Tasks are defined with dependencies, ensuring they run in the correct order.
- **Parallel Execution**: Dagra automatically runs tasks in parallel when their dependencies are satisfied, speeding up the overall workflow.
- **YAML Configuration**: A simple and human-readable YAML format is used to define tasks.
- **Dry-Run Mode**: A `--dry-run` flag allows you to preview the execution plan without running any commands.
- **Robust Validation**: The dependency graph is validated for missing tasks and circular dependencies before execution.

## Project Structure

The project is organized into several key modules, each with a specific responsibility:

- [**CLI**](./cli/parser.md): Handles command-line argument parsing and YAML file loading.
- [**Core**](./core/): Contains the fundamental data structures, including the `Task` and the `Dag`.
  - [Task](./core/task.md)
  - [DAG](./core/dag.md)
- [**Execution**](./execution/runner.md): Manages the parallel execution of tasks.
- [**Utils**](./utils/logger.md): Provides utility functions, such as the colorful logger.

## Getting Started

To get started with Dagra, you need a C++17 compatible compiler and CMake. The dependencies (`yaml-cpp` and `gtest`) are fetched automatically during the build process.

1.  **Clone the repository.**
2.  **Build the project:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
3.  **Run Dagra with a configuration file:**
    ```bash
    ./dagra path/to/your/config.yaml
    ```
