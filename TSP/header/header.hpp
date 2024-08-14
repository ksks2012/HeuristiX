#ifndef __HEADER_HPP__
#define __HEADER_HPP__

// standard libraries
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <getopt.h>

#include "node.hpp"

// algorithms

using namespace std;

typedef double (*EvaluateFunctionPointer)(std::vector<Node>&);

#endif