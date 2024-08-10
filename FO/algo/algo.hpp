#ifndef ALGO_HPP
#define ALGO_HPP

#include "header.hpp"
#include "utils.hpp"

class Algo {
public:
    FOBenchmark *benchmark;
    
    int population_size;
    int iteration;
    int func_number;
private:    
public:
    Algo();
    virtual void intialize_data() = 0;
    virtual void run() = 0;
    virtual void evaluate() = 0;

    double random_double(double, double);
    void set_func_number(int);
};

#endif // ALGO_HPP