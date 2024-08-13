#ifndef GA_HPP
#define GA_HPP

#include "../algo.hpp"

class GA : public Algo {
private:
    double crossover_rate;
    double mutation_rate;
public:

private:
    void initialize_population();
    void update_population();
    void update_global_best();

    void crossover();
    void mutation();

public:
    GA();
    GA(YAML::Node);
    void intialize_data() override;
    void run() override;
    void evaluate() override;
};

#endif // GA_HPP