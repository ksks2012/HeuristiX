#!/bin/bash
# Script: build.sh
# Description: This script is used to build the TSP meta-heuristic program.
# Author: ksks2012
# Version: 1.0

make clean all
../cmd/tsp_solver  -algo SA -dataset ../dataset/pr76.tsp
../cmd/tsp_solver  -algo TABU -dataset ../dataset/pr76.tsp