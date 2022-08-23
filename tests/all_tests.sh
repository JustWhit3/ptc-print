#!/bin/bash

# $1 = normal: run normal tests
# $1 = macro: run tests with preprocessor directives

# run_all_tests
run_all_tests() {

    # System tests
    echo ""
    echo "======================================================"
    echo "     SYSTEM TESTS"
    echo "======================================================"
    echo ""
    ./bin/system_tests

    # Memory tests
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
}

# All tests
if [ "$1" == "normal" ] ; then
    echo "======================================================"
    echo "     COMPILING"
    echo "======================================================"
    echo ""
    make
    run_all_tests
elif [ "$1" == "macro" ] ; then
    echo "======================================================"
    echo "     COMPILING WITH PREPROECESSOR DIRECTIVES"
    echo "======================================================"
    echo ""
    sed -i '4s/.*/#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS\n/' system_tests.cpp
    sed -i '4s/.*/#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS\n/' threading_tests.cpp
    sed -i '6s/.*/#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS\n/' unit_tests.cpp
    make
    run_all_tests
    sed -i '4d' system_tests.cpp
    sed -i '4d' threading_tests.cpp
    sed -i '6d' unit_tests.cpp
else
    echo "======================================================"
    echo "     COMPILING"
    echo "======================================================"
    echo ""
    make
    run_all_tests
    echo ""
    echo "======================================================"
    echo "     RE-COMPILING WITH PREPROECESSOR DIRECTIVES"
    echo "======================================================"
    echo ""
    make clean
    sed -i '4s/.*/#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS\n/' system_tests.cpp
    sed -i '4s/.*/#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS\n/' threading_tests.cpp
    sed -i '6s/.*/#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS\n/' unit_tests.cpp
    make
    run_all_tests
    sed -i '4d' system_tests.cpp
    sed -i '4d' threading_tests.cpp
    sed -i '6d' unit_tests.cpp
fi

# Cppcheck
echo ""
echo "======================================================"
echo "     CPPCHECK TESTS"
echo "======================================================"
echo ""
cppcheck ../include/ptc/print.hpp