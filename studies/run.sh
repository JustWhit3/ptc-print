#!/bin/bash

mkdir -p data

./bin/benchmarking \
--benchmark_out=data/print.json \
--benchmark_repetitions=1 \
--benchmark_display_aggregates_only=false \
--benchmark_report_aggregates_only=false