#!/bin/bash

# Launching benchmarks
sudo cpupower frequency-set --governor performance > /dev/null 2>&1

./analysis.py \
--niter=100 \
--plots=yes

sudo cpupower frequency-set --governor powersave > /dev/null 2>&1
