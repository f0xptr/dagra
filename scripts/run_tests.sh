#!/bin/bash
#
# run_tests.sh - A script to run the project's test suite.
#
# This script navigates to the build directory and runs CTest. It assumes
# the project has already been built.
#

set -e

# Check if build directory exists
if [ ! -d "build" ]; then
    echo "Error: build/ directory not found. Please run scripts/build.sh first."
    exit 1
fi

# Run tests
echo "Running tests..."
cd build
ctest --output-on-failure
cd ..

echo "Tests complete."
