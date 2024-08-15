#ifndef ABC_HPP
#define ABC_HPP


#include "../algo.hpp"

class ABC : public Algo {
private:
    vector<int> trails;
public:
    // data for algorithm
    vector<double> probability_list;

    // parameters for algorithm
    int limit_trail;

private:
    void initialize_population() override;
    void update_population() override;
    void update_global_best() override;

    void employed_bees();
    void onlooker_bees();
    void scout_bees();

    void build_probability_list();

    // fitness function of ABC
    double cal_honey_source(double);

public:
    ABC();
    ABC(YAML::Node);
    void intialize_data() override;
};
#endif // ABC_HPP