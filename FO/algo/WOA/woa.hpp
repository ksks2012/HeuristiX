#ifndef WOA_HPP
#define WOA_HPP

#include "algo.hpp"

class WOA : public Algo {
private:
    double a;
    double c;

    vector<vector<double>> D;
public:

private:
    void initialize_population() override;
    void update_population() override;
    void update_global_best() override;

    void encircling_prey();
    void spiral_updating();
    void exploration();
    void update_weights();

    inline double cal_A();
    inline double cal_C();
public:
    WOA();
    WOA(YAML::Node);
    void intialize_data() override;
};

#endif // WOA_HPP