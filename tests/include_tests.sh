#!/bin/bash

#====================================================
#     Variables
#====================================================
INCL=include_tests.cpp

#====================================================
#     Procedure
#====================================================
cp system_tests.cpp ${INCL}
sed -i '6s/.*/#include <ptc\/print.hpp>/' ${INCL}
g++ -std=c++17 -pthread include_tests.cpp
rm include_tests.cpp a.out