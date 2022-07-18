#!/bin/bash

# System tests
./bin/system_tests

# Unit tests
./bin/unit_tests

# Include tests
./include_tests.sh

# Valgrind tests
./profiling.sh memcheck ./bin/system_tests
./profiling.sh helgrind ./bin/system_tests