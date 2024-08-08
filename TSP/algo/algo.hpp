#ifndef ALGO_HPP
#define ALGO_HPP

#include "header.hpp"
#include "node.hpp"

class Algo {
public:
    int node_size;
    std::vector<Node> data;
    std::vector<std::vector<double>> distance;
private:
    
public:
    Algo();
    virtual void run() = 0;
    virtual void set_data(std::vector<Node> &data) = 0;

    // common functions
    void calculate_distance_table();
    double get_distance_table(int, int);

    void two_opt(std::vector<Node>& path);
    void three_opt(std::vector<Node>& path);
};

#endif // ALGO_HPP