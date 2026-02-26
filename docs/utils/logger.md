# Utils Module: Logger

The `utils` module provides common utilities for the Dagra application. The most prominent utility is the `Logger` class, which offers a thread-safe and colorful logging interface.

## Logger Class

**File:** `include/dagra/utils/logger.hpp`

The `Logger` is a static class, meaning you can call its methods directly without needing to create an instance of it. It is designed to be used from anywhere in the application, including from multiple threads simultaneously.

### Features

-   **Thread Safety**: All logging methods are protected by a `std::mutex` to prevent garbled output when called from multiple threads.
-   **Color-Coded Output**: The logger uses ANSI escape codes to color-code messages based on their severity level, making the console output easier to read.
-   **Multiple Log Levels**: The logger provides several static methods for different types of messages.

### Log Levels and Methods

-   `Logger::info(const std::string& message)`: For general informational messages. Output is in the default terminal color.

-   `Logger::success(const std::string& message)`: For indicating the successful completion of an operation. Output is in **green**.

-   `Logger::warn(const std::string& message)`: For warning messages that do not constitute an error but may require attention. Output is in **yellow**.

-   `Logger::error(const std::string& message)`: For error messages. This method writes to the standard error stream (`std::cerr`) and the output is in **red**.

-   `Logger::dry_run(const std::string& message)`: A special level for messages related to dry-run mode. Output is in **cyan**.

## Usage Example

```cpp
#include "dagra/utils/logger.hpp"

// ...

dagra::utils::Logger::info("Starting the application...");
dagra::utils::Logger::success("Task 'build' completed.");
dagra::utils::Logger::error("Failed to execute task 'test'.");
```
