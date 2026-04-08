# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.1.0] - 2026-04-08

### Added
- **Timeout support**: Tasks can now specify an optional `timeout` field (in seconds) to automatically terminate long-running commands.
- **Environment variables**: Tasks can define environment variables via the `env` field in YAML configuration.
- **File existence validation**: The parser now verifies that the configuration file exists before attempting to parse it.
- **Enhanced error messages**: More descriptive error handling for missing configuration files and invalid file paths.
- **Improved dry-run output**: Dry-run mode now displays timeout and environment variable information for each task.

### Changed
- Updated `Task` structure to include `timeout_seconds` and `env_vars` fields.
- Enhanced YAML parser to support new task configuration options.
- Improved task execution logic with environment variable injection.
- Updated all file version headers to 1.1.0.

### Fixed
- Better error reporting when timeout is exceeded during task execution.

## [1.0.0] - 2026-02-26

### Added
- Initial implementation of Dagra, a DAG-based task runner.
- Core components: `Dag`, `Task`, `Parser`, `Runner`.
- Parallel execution of tasks with dependency resolution.
- YAML configuration for defining tasks.
- `--dry-run` mode to simulate execution.
- Colorful, thread-safe logger.
- Unit tests for all core components using GoogleTest.
- `docs/` directory with detailed documentation for all modules.
- GitHub Actions CI workflow for automated builds and testing.
- Issue and pull request templates for community contributions.
- `CODE_OF_CONDUCT.md`, `CONTRIBUTING.md`, and `CONTRIBUTORS.md`.
- `.gitignore`, `.gitattributes`, and `.editorconfig` for consistent development.
- `.clang-format` and `.clang-tidy` for code quality.
- Utility scripts for formatting, linting, building, and testing.
