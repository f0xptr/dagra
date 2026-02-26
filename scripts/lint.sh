#!/bin/bash
#
# lint.sh - A script to run clang-tidy for static analysis.
#
# This script checks for the existence of a compile_commands.json file,
# which is required by clang-tidy, and then runs clang-tidy on all C++
# source files in the project.
#

set -e

# Check if compile_commands.json exists
if [ ! -f "build/compile_commands.json" ]; then
    echo "Error: compile_commands.json not found in the build/ directory."
    echo "Please configure the project with CMake using: cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
    exit 1
fi

# Find all C++ source files
files=$(find src/ tests/ -type f -name "*.cpp")

# Run clang-tidy
echo "Running clang-tidy..."
clang-tidy -p build/ $files

echo "Linting complete."
