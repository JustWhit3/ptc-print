#!/bin/bash

# $1 = "macro": run benchmarks with macro options enabled.

# Creating directories
mkdir -p data

# Extra option for macro usage
if [ "$1" == "macro" ] ; then
    sed -i '4s/.*/#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS\n/' benchmarking.cpp
fi

# Compiling
cmake --build build

# Setting-up environment
sudo cpupower frequency-set --governor performance > /dev/null 2>&1                  # Set scaling_governor to "performance"
echo "1" | sudo tee /sys/devices/system/cpu/intel_pstate/no_turbo > /dev/null 2>&1   # Disable Turboboost
echo 3 | sudo tee /proc/sys/vm/drop_caches > /dev/null 2>&1                          # Drop file system cache
sync
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space > /dev/null 2>&1               # Disable address space randomization

# Generating benchmarking data
./build/benchmarking \
--benchmark_out=data/benchmarking.json \
--benchmark_repetitions=15 \
--benchmark_display_aggregates_only=true \
--benchmark_report_aggregates_only=true

# Setting-up environment back to old settings
sudo cpupower frequency-set --governor powersave > /dev/null 2>&1
echo "0" | sudo tee /sys/devices/system/cpu/intel_pstate/no_turbo > /dev/null 2>&1
echo "" | sudo tee /proc/sys/vm/drop_caches > /dev/null 2>&1
sync
echo 2 | sudo tee /proc/sys/kernel/randomize_va_space > /dev/null 2>&1

# Extra option for macro usage
if [ "$1" == "macro" ] ; then
    sed -i '4d' benchmarking.cpp
fi

# Analyzing data
./analysis.py \
--tests=on \
--data=data/benchmarking.json \
--save=no \
--macro=no