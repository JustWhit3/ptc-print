#!/bin/bash

# Compilation
echo "======================================================"
echo "     COMPILING"
echo "======================================================"
echo ""
make

# System tests
echo ""
echo "======================================================"
echo "     SYSTEM TESTS"
echo "======================================================"
echo ""
./bin/system_tests

# Memory tests
echo ""
echo ""
echo "======================================================"
echo "     MEMORY TESTS"
echo "======================================================"
./profiling.sh memcheck ./bin/system_tests

# Threading tests
echo ""
echo "======================================================"
echo "     THREADING TESTS"
echo "======================================================"
echo ""
./bin/threading_tests
./profiling.sh helgrind ./bin/threading_tests

# Unit tests
echo ""
echo "======================================================"
echo "     UNIT TESTS"
echo "======================================================"
echo ""
./bin/unit_tests

# Include tests
echo ""
echo "======================================================"
echo "     INCLUDE TESTS"
echo "======================================================"
echo ""
if ./include_tests.sh ; then
    echo "Passed!"
fi

# Cppcheck
echo ""
echo "======================================================"
echo "     CPPCHECK TESTS"
echo "======================================================"
echo ""
cppcheck ../include/ptc/print.hpp