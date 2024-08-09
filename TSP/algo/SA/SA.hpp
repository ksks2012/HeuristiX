#ifndef SA_HPP
#define SA_HPP

#include "algo.hpp"
#include "node.hpp"

// TODO: class of Problem
class SA : public Algo {
private:
public:
    ;
private:
    double calculate_result(const std::vector<Node>&);
    double acceptance_probability(double, double, double);
public:
    SA();

    void run();
};

#endif // SA_HPP