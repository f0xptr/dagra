# Dagra

Dagra is a simple yet powerful task runner based on a Directed Acyclic Graph (DAG). It is designed to execute a series of tasks with specified dependencies, making it an ideal tool for build automation, data processing pipelines, and other complex workflows.

## Key Features

-   **DAG-based Execution**: Tasks are defined with dependencies, ensuring they run in the correct order.
-   **Parallel Execution**: Dagra automatically runs tasks in parallel when their dependencies are satisfied, speeding up the overall workflow.
-   **YAML Configuration**: A simple and human-readable YAML format is used to define tasks.
-   **Dry-Run Mode**: A `--dry-run` flag allows you to preview the execution plan without running any commands.
-   **Robust Validation**: The dependency graph is validated for missing tasks and circular dependencies before execution.

## Getting Started

To get started with Dagra, you need a C++17 compatible compiler and CMake.

### 1. Build the project

We provide a simple script to build the project:

```bash
./scripts/build.sh
```

### 2. Run Dagra

Create a `config.yaml` file to define your tasks:

```yaml
tasks:
  - id: hello
    command: "echo 'Hello from Dagra!'"
  - id: world
    command: "echo 'World is waiting for hello.'"
    depends_on:
      - hello
```

Then, run Dagra with your configuration file:

```bash
./build/dagra config.yaml
```

## Documentation

For more detailed information on the project's architecture and components, please see the [full documentation](./docs/index.md).

## Contributing

Contributions are welcome! Please see our [Contributing Guidelines](./CONTRIBUTING.md) to get started.

## License

This project is licensed under the terms of the MIT license.
