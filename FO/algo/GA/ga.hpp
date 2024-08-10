#ifndef GA_HPP
#define GA_HPP

#include "../algo.hpp"

class GA : public Algo {
private:
    double crossover_rate;
    double mutation_rate;
public:
    vector<vector<double>> population;
    vector<double> fitness;
    vector<double> pbest;
    vector<double> gbest;
    vector<double> pbest_fitness;
    double gbest_fitness;

private:
    void initialize_population();
    void update_population();
    void update_global_best();

    void crossover();
    void mutation();

public:
    GA();
    void intialize_data() override;
    void run() override;
    void evaluate() override;


    void show_population();
    void show_gbest();
};

#endif // GA_HPP