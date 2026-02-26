# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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
