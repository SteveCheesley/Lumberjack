#!/bin/bash

setTestCommand() {
  test_command="./build/lumberjack_${test_type}_tests"  
}

# Initialise Variables
test_type=""
test_type_set_flag=0
test_filter=""
list_test_flag=0
build_skip=0

# Parse the options
while getopts "f:t:ls" opt; do
  case $opt in
    t)
      test_type=$OPTARG
      test_type_set_flag=1;
      ;;
    f)
      test_filter=$OPTARG
      ;;
    l)
      list_test_flag=1
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

setTestCommand

listTestOfType() {
  test_type=$1
  echo ""
  echo "...::: Listing $test_type tests :::..."
  setTestCommand
  eval "$test_command --gtest_list_tests"
}

# Determine the operation based on the flags provided
if [[ $list_test_flag -eq 1 && $test_type_set_flag -eq 1 ]]; then
  eval "$test_command --gtest_list_tests"
  exit $?
elif [[ $list_test_flag -eq 1 && $test_type_set_flag -eq 0 ]]; then
  listTestOfType "unit"
  listTestOfType "integration"
  exit $?
elif [ -n "$test_filter" ]; then
  if [ $test_type_set_flag -eq 0 ]; then
    echo "ERROR: Unable to select a test filter without specifying type (-t)"
    exit 1;
  fi
  echo "..:: Executing with filter [$test_filter] ::.."
  eval "$test_command --gtest_filter=$test_filter"
  exit $?
else
  ## TODO - Add in a nested if that will only run the suite executable that is specified in "type"
  echo "..:: Executing all tests in the suite ::.."
  ctest --test-dir build --output-on-failure
  exit $?
fi
