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
    void initialize_population() override;
    void update_population() override;
    void update_global_best() override;

public:
    PSO();
    PSO(YAML::Node);
    void intialize_data() override;

    void show_velocity();
};

#endif // PSO_HPP