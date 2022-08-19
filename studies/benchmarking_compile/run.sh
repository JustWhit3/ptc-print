#!/bin/bash

# Launching benchmarks
sudo cpupower frequency-set --governor performance > /dev/null 2>&1

./scripts/get_time.py \
--tests=on \
--niter=2 \
--plots=no

sudo cpupower frequency-set --governor powersave > /dev/null 2>&1
