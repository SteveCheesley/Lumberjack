#!/bin/bash

# Clear away any old, stale builds that are present
echo "..:: Cleaning the build/ directory ::.."
rm -frv build

# Prepare the automated build instructions (CMake)
echo "..:: Preparing build instructions ::.."
cmake -S . -B build -G Ninja