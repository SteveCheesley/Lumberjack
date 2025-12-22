#!/bin/bash

# Clear away any old, stale builds that are present
echo "..:: Cleaning the build/ directory ::.."
rm -frv build

# Prepare the automated build instructions (CMake)
while getopts ":d" option; do
    case $option in
        d)
         echo "..:: Preparing DEBUG build instructions... ::.."
         cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
         exit;;
    esac
done

echo "..:: Preparing build instructions... ::.."
cmake -S . -B build -G Ninja