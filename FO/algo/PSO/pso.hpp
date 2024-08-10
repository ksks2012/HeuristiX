#ifndef PSO_HPP
#define PSO_HPP

#include "../algo.hpp"

class PSO : public Algo {
public:
    // data for algorithm
    std::vector<std::vector<double>> population;
    std::vector<std::vector<double>> velocity;
    std::vector<double> fitness;
    std::vector<double> pbest;
    std::vector<double> gbest;
    std::vector<double> pbest_fitness;
    double gbest_fitness;

    // parameters for algorithm
    double w, c1, c2;
    double vrate;
    std::vector<double> vmax, vmin;

private:
    void initialize_particles();
    void update_particles();
    void update_global_best();

public:
    PSO();
    void intialize_data() override;
    void run() override;
    void evaluate() override;

    void show_population();
    void show_velocity();
    void show_gbest();
};

#endif // PSO_HPP