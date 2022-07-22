#!/bin/bash

mkdir -p data

sudo cpupower frequency-set --governor performance > /dev/null 2>&1

./bin/benchmarking \
--benchmark_out=data/benchmarking.json \
--benchmark_repetitions=15 \
--benchmark_display_aggregates_only=true \
--benchmark_report_aggregates_only=true