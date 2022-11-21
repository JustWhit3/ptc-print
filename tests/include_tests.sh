#!/bin/bash

#====================================================
#     Standard include
#====================================================
cp tests/system_tests.cpp tests/include_tests.cpp
sed -i '6s/.*/#include <ptc\/print.hpp>/' tests/include_tests.cpp
g++ -std=c++17 -pthread tests/include_tests.cpp
rm tests/include_tests.cpp a.out

#====================================================
#     Multiple include
#====================================================
touch tests/include_one.hpp
echo "#ifndef INCLUDE_ONE" >> tests/include_one.hpp
echo "#define INCLUDE_ONE" >> tests/include_one.hpp
echo "#include <ptc/print.hpp>" >> tests/include_one.hpp
echo "#endif" >> tests/include_one.hpp
touch tests/include_two.hpp
echo "#ifndef INCLUDE_TWO" >> tests/include_two.hpp
echo "#define INCLUDE_TWO" >> tests/include_two.hpp
echo "#include <ptc/print.hpp>" >> tests/include_two.hpp
echo "#endif" >> tests/include_two.hpp
touch tests/multiple_include.cpp
echo "#include \"include_one.hpp\"" >> tests/multiple_include.cpp
echo "#include \"include_two.hpp\"" >> tests/multiple_include.cpp
echo "int main() {}" >> tests/multiple_include.cpp
g++ -std=c++17 tests/multiple_include.cpp
rm tests/include_one.hpp
rm tests/include_two.hpp
rm tests/multiple_include.cpp