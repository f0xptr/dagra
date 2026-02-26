#!/bin/bash
#
# build.sh - A script to configure and build the project.
#
# This script creates a build directory, runs CMake to configure the project,
# and then builds the project using the generated build system.
#

set -e

# Create build directory
mkdir -p build

# Configure with CMake
echo "Configuring with CMake..."
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build the project
echo "Building project..."
cmake --build build

echo "Build complete."
