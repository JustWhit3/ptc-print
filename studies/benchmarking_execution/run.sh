#!/bin/bash

# $1 = "macro": run benchmarks with macro options enabled.

# Creating directories
mkdir -p data

# Extra option for macro usage
if [ "$1" == "macro" ] ; then
    sed -i '4s/.*/#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS\n/' benchmarking.cpp
fi

# Generating benchmarking data
make
sudo cpupower frequency-set --governor performance > /dev/null 2>&1
./bin/benchmarking \
--benchmark_out=data/benchmarking.json \
--benchmark_repetitions=15 \
--benchmark_display_aggregates_only=true \
--benchmark_report_aggregates_only=true
sudo cpupower frequency-set --governor powersave > /dev/null 2>&1

# Extra option for macro usage
if [ "$1" == "macro" ] ; then
    sed -i '4d' benchmarking.cpp
    sed -i '4d' benchmarking.cpp
fi

# Analyzing data
./analysis.py \
--tests=on \
--data=data/benchmarking.json \
--save=no \
--macro=no