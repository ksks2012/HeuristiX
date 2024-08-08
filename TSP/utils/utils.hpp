#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

#include "header.hpp"
#include "node.hpp"

vector<Node> read_nodes(string &);
double calculate_distance(const Node&, const Node&);

#endif // UTILS_HPP