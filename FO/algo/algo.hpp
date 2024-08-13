#ifndef ALGO_HPP
#define ALGO_HPP

#include "header.hpp"
#include "utils.hpp"

class Algo {
public:
    FOBenchmark *benchmark;
    
    vector<vector<double>> population;
    vector<double> fitness;
    vector<double> pbest;
    vector<double> gbest;
    vector<double> pbest_fitness;
    double gbest_fitness;


    int population_size;
    int iteration;
    int func_number;
private:    
public:
    Algo();
    virtual void intialize_data() = 0;
    virtual void run() = 0;
    virtual void evaluate() = 0;

    int random_int(int, int);
    double random_double(double, double);
    int RWS();

    void set_func_number(int);

    // show data
    void show_population();
    void show_gbest();

};

#endif // ALGO_HPP