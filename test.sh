#!/bin/bash

# Compile sources (both lib and test)
echo "..:: Building resources to include latest changes ::.."
./build.sh

while getopts t: flag
do
    case "${flag}" in
        t) testFlag=${OPTARG};;
    esac
done

if [ -n "$testFlag" ] 
then
    echo "..:: Executing '$testFlag' ::.."
    ./build/lumberjack_tests --gtest_filter=$testFlag
else
    # Execute tests
    echo "..:: Executing all tests in the suite ::.."
    ctest --test-dir build --output-on-failure
fi
echo "..:: Test Execution Complete ::.."
