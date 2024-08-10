#ifndef UTILS_HPP
#define UTILS_HPP

#include "header.hpp"
class Benchmark {
public:
    vector<double> upper_bound, lower_bound;
    int dimentions;
};

class FOBenchmark : public Benchmark {
public:
    vector<double> OShift, M, y, z, x_bound;
    int ini_flag = 0, n_flag, func_flag;
    vector<int> SS;

private:
    void bent_cigar_func(const vector<double>& , double& , int, vector<double>& , vector<double>& , int, int);
    /* shift and rotate */
    void sr_func(const vector<double>& , vector<double>& , int, vector<double>& , vector<double>& , double, int, int); 

    void shiftfunc(const vector<double>& , vector<double>& , int, vector<double>& );
    void rotatefunc(vector<double>& , vector<double>& , int, vector<double>& );
public:
    FOBenchmark();
    FOBenchmark(int);

    void set_bounds(int, int);
    void set_dimensions(int);

    void cec17_test_func(const vector<vector<double>>&, vector<double>&, int, int, int);
};

#define INF 1.0e99
#define EPS 1.0e-14
#define E 2.7182818284590452353602874713526625
#define PI 3.1415926535897932384626433832795029

#endif // UTILS_HPP