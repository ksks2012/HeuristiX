#ifndef PSO_HPP
#define PSO_HPP

#include "../algo.hpp"

class PSO : public Algo {
public:
    // data for algorithm
    vector<vector<double>> velocity;

    // parameters for algorithm
    double w, c1, c2;
    double vrate;
    vector<double> vmax, vmin;

private:
    void initialize_particles();
    void update_particles();
    void update_global_best();

public:
    PSO();
    PSO(YAML::Node);
    void intialize_data() override;
    void run() override;

    void show_velocity();
};

#endif // PSO_HPP