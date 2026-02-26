# CLI Module

The `cli` module is responsible for handling all command-line interactions for the Dagra application. Its primary component is the `Parser` class, which processes command-line arguments and loads the task configuration from a YAML file.

## Parser

**File:** `include/dagra/cli/parser.hpp`

The `Parser` class provides a static interface for parsing the application's input.

### `AppOptions` Struct

This struct holds the configuration extracted from the command-line arguments.

-   `config_filepath` (std::string): The path to the user-provided YAML configuration file.
-   `dry_run` (bool): A flag that is `true` if the `--dry-run` option is specified.

### `parse_args(int argc, char* argv[])`

This static method processes the raw command-line arguments.

-   It expects at least one argument: the path to the configuration file.
-   It also checks for the optional `--dry-run` flag.
-   **Returns**: An `AppOptions` struct populated with the parsed values.
-   **Throws**: `std::runtime_error` if the configuration file path is missing.

### `parse_yaml(const std::string& filepath)`

This static method reads and parses the YAML configuration file specified by the `filepath`.

-   It expects the YAML file to have a top-level key named `tasks`, which should be a sequence of task objects.
-   Each task object must have an `id` and a `command`. An optional `depends_on` field can be provided as a sequence of task IDs.
-   **Returns**: A `std::vector<core::Task>` containing the tasks defined in the file.
-   **Throws**: `std::runtime_error` if the file format is invalid, a task is malformed, or the file cannot be opened.

## Usage Example

The `Parser` is used in `main.cpp` to initialize the application:

```cpp
// In main.cpp
try {
    // 1. Parse command-line arguments
    dagra::cli::AppOptions options = dagra::cli::Parser::parse_args(argc, argv);
    
    // 2. Parse the YAML file
    auto tasks = dagra::cli::Parser::parse_yaml(options.config_filepath);
    
    // ... proceed with DAG creation and execution
} catch (const std::exception& e) {
    // Handle parsing errors
}
```
