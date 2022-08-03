#!/bin/bash

#====================================================
#     Variables
#====================================================
INCL=include_tests.cpp

#====================================================
#     Standard include
#====================================================
cp system_tests.cpp ${INCL}
sed -i '6s/.*/#include <ptc\/print.hpp>/' ${INCL}
g++ -std=c++17 -pthread include_tests.cpp
rm include_tests.cpp a.out

#====================================================
#     Multiple include
#====================================================
touch include_one.hpp
echo "#ifndef INCLUDE_ONE" > include_one.hpp
echo "#define INCLUDE_ONE" > include_one.hpp
echo "#include <ptc/print.hpp>" > include_one.hpp
echo "#endif" > include_one.hpp
touch include_two.hpp
echo "#ifndef INCLUDE_TWO" > include_two.hpp
echo "#define INCLUDE_TWO" > include_two.hpp
echo "#include <ptc/print.hpp>" > include_two.hpp
echo "#endif" > include_two.hpp
touch multiple_include.cpp
echo "#include \"include_one.hpp\"" > multiple_include.cpp
echo "#include \"include_two.hpp\"" > multiple_include.cpp
echo "int main() {}" > multiple_include.cpp
rm include_one.hpp
rm include_two.hpp
rm multiple_include.cpp