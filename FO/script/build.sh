#!/bin/bash
# Script: build.sh
# Description: This script is used to build the Funtion Optimization meta-heuristic program.
# Author: ksks2012
# Version: 1.0

make clean func
../cmd/benchmark

make clean all
../cmd/fo_solver -algo PSO -func 1 -dim 100