#!/bin/bash
# Script: build.sh
# Description: This script is used to build the Funtion Optimization meta-heuristic program.
# Author: ksks2012
# Version: 1.0

# Check Benchmark
make clean func
../cmd/benchmark

make clean all

# PSO
../cmd/fo_solver --algo=PSO --func=1 --dim=2 --conf=../etc/config.yml

# GA
../cmd/fo_solver --algo=GA --func=1 --dim=2 --conf=../etc/config.yml

# ABC
../cmd/fo_solver --algo=ABC --func=1 --dim=2 --conf=../etc/config.yml

# GWO
../cmd/fo_solver --algo=GWO --func=1 --dim=2 --conf=../etc/config.yml