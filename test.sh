#!/bin/bash

# Compile sources (both lib and test)
./build.sh

# Execute tests
ctest --test-dir build --output-on-failure