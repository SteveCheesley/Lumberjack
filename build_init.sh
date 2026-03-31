#!/bin/bash

# Initialise Variables
debug_flag=0
test_build_flag=0
cmake_options=""

# Clear away any old, stale builds that are present
echo "..:: Cleaning the "build/" directory... ::.."
rm -frv build

# Prepare the automated build instructions (CMake)
while getopts "dtml" option; do
    case $option in
        d)
         echo "* Adding DEBUG build instructions..."
         cmake_options="$cmake_options -DCMAKE_BUILD_TYPE=Debug"
         ;;
        t)
         echo "* Adding 'Unit Test' build instructions..."
         cmake_options="$cmake_options -DLUMBERJACK_BUILD_TESTS=ON"
         ;;
        m)
         echo "* Adding Memory Testing build instructions..."
         cmake_options="$cmake_options -DLUMBERJACK_ENABLE_ASAN=ON"
         ;;
        l)
         echo "* Adding 'Clang Tidy [linter]' build instructions..."
         cmake_options="$cmake_options -DENABLE_CLANG_TIDY=ON"
         ;;
    esac
done

echo "..:: Preparing build instructions... ::.."
full_command="cmake -S . -B build -G Ninja$cmake_options"

echo "Executing: $full_command"
$full_command