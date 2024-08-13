#!/bin/bash
# Script: build.sh
# Description: This script is used to build the Funtion Optimization meta-heuristic program.
# Author: ksks2012
# Version: 1.0

# Check Benchmark
make clean func
../cmd/benchmark

# PSO
make clean all
../cmd/fo_solver --algo=PSO --func=1 --dim=100 --conf=../etc/config.yml

# GA
make clean all
../cmd/fo_solver --algo=GA --func=1 --dim=2 --conf=../etc/config.yml

# ABC
make clean all
../cmd/fo_solver --algo=ABC --func=1 --dim=2 --conf=../etc/config.yml