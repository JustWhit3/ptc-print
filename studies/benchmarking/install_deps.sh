#!/bin/bash

# Install fmt
git clone https://github.com/fmtlib/fmt.git
cd fmt || exit
mkdir build
cd build || exit
cmake ..
make
make tests
sudo make install