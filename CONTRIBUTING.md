# Contributing to Dagra

First off, thank you for considering contributing to Dagra! It's people like you that make Dagra such a great tool.

## Where do I start?

If you're new to the project, here are some ways you can contribute:

-   **Reporting Bugs**: If you find a bug, please open a [bug report issue](https://github.com/f0xptr/dagra/issues/new?template=bug_report.md).
-   **Suggesting Features**: If you have an idea for a new feature, please open a [feature request issue](https://github.com/f0xptr/dagra/issues/new?template=feature_request.md).
-   **Asking Questions**: If you have a question, you can open a [question issue](https://github.com/f0xptr/dagra/issues/new?template=question.md).

## Development Setup

To get started with the development of Dagra, you'll need a C++17 compatible compiler and CMake.

1.  **Fork and Clone**: Fork the repository on GitHub and clone your fork locally.
    ```bash
    git clone https://github.com/YOUR_USERNAME/dagra.git
    cd dagra
    ```

2.  **Build the project**: We provide a simple build script to configure and build the project.
    ```bash
    ./scripts/build.sh
    ```

3.  **Run the tests**: After building, you can run the tests to ensure everything is working correctly.
    ```bash
    ./scripts/run_tests.sh
    ```

## Contribution Workflow

We follow a standard "fork and pull" workflow.

1.  **Create a new branch**: Before making any changes, create a new branch for your feature or bug fix.
    ```bash
    git checkout -b my-new-feature
    ```

2.  **Make your changes**: Make your changes to the codebase. Please ensure your code follows the project's style guidelines. You can use the `format.sh` script to format your code.
    ```bash
    ./scripts/format.sh
    ```

3.  **Commit your changes**: Commit your changes with a clear and descriptive commit message.
    ```bash
    git commit -am "feat: Add some amazing feature"
    ```

4.  **Push to your fork**: Push your changes to your fork on GitHub.
    ```bash
    git push origin my-new-feature
    ```

5.  **Open a Pull Request**: Open a pull request from your fork to the `main` branch of the original repository. Please fill out the pull request template with as much detail as possible.

Thank you for your contribution!
