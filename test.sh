#!/bin/bash

# Compile sources (both lib and test)
echo "..:: Building resources to include latest changes ::.."
./build.sh

# Initialise Variables
t_arg=""
l_flag=0

# Parse the options
while getopts "t:l" opt; do
  case $opt in
    t)
      t_arg=$OPTARG
      ;;
    l)
      l_flag=1
      ;;
  esac
done

# Determine the operation based on the flags provided
if [ $l_flag -eq 1 ]; then
    ./build/lumberjack_tests --gtest_list_tests
    exit 0
elif [ -n "$t_arg" ]; then
    echo "..:: Executing '$t_arg' ::.."
    ./build/lumberjack_tests --gtest_filter=$t_arg
    exit 0
else
    echo "..:: Executing all tests in the suite ::.."
    ctest --test-dir build --output-on-failure
    exit 0;
fi
