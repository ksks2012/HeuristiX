#ifndef ALGO_HPP
#define ALGO_HPP

#include "header.hpp"
#include "node.hpp"

class Algo {
public:
    int node_size;
    std::vector<Node> data;
    std::vector<std::vector<double>> distance;

    // TODO: function pointer to evaluate the solution in each problem
    EvaluateFunctionPointer evaluate_solution;
private:
    
public:
    Algo();
    void set_data(std::vector<Node> &);
    virtual void run() = 0;
    
    // common functions
    void calculate_distance_table();
    double get_distance_table(int, int);

    // exchange methods
    void two_opt(std::vector<Node>& path);
    void three_opt(std::vector<Node>& path);
    void random_switch(std::vector<Node>& path);
};

#endif // ALGO_HPP