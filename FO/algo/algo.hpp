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
    int max_evaluation;
    int func_number;

    int evaluation_count;
private:    
public:
    Algo();
    void run();

    virtual void intialize_data() = 0;
    virtual void initialize_population() = 0;
    virtual void update_population() = 0;
    virtual void update_global_best() = 0;

    int random_int(int, int);
    double random_double(double, double);
    int RWS();

    void set_func_number(int);
    void evaluate();

    // show data
    void show_population();
    void show_gbest();
};

#endif // ALGO_HPP