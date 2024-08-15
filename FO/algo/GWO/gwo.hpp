#ifndef GWO_HPP
#define GWO_HPP

#include "algo.hpp"

class GWO : public Algo {
private:
    vector<double> alpha;
    vector<double> beta;
    vector<double> delta;
    int alpha_index;
    int beta_index;
    int delta_index;

    double a;
    double c;
public:

private:
    void initialize_population() override;
    void update_population() override;
    void update_global_best() override;

    void encircling_prey();
    void hunting();

    void update_weights();
    inline double cal_A();
    inline double cal_C();

public:
    GWO();
    GWO(YAML::Node);
    void intialize_data() override;
};

#endif // GWO_HPP