#!/bin/bash
#
# format.sh - A script to format the C++ source code using clang-format.
#
# This script finds all .cpp and .hpp files in the src/, include/, and tests/
# directories and applies the formatting rules defined in the .clang-format file.
#

set -e

# Find all C++ source and header files
files=$(find src/ include/ tests/ -type f \( -name "*.cpp" -o -name "*.hpp" \))

# Run clang-format on the files
echo "Formatting C++ files..."
clang-format -i -style=file $files

echo "Formatting complete."
