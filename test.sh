#!/bin/bash

# Initialise Variables
t_arg=""
l_flag=0
build_skip=0

# Parse the options
while getopts "t:ls" opt; do
  case $opt in
    t)
      t_arg=$OPTARG
      ;;
    l)
      l_flag=1
      ;;
    s)
      build_skip=1
      ;;
  esac
done

# Compile sources (both lib and test) - [unless skipped]
if [ $build_skip -eq 0 ]; then
  echo "..:: Building resources to include latest changes ::.."
  ./build_init.sh -t
  ./build.sh
fi


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
