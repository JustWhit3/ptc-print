#!/bin/bash

mkdir -p data

./bin/benchmarking \
--benchmark_out=data/benchmarking.json \
--benchmark_repetitions=10 \
--benchmark_display_aggregates_only=true \
--benchmark_report_aggregates_only=true