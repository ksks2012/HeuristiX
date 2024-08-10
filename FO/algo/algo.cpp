#include "algo.hpp"
#include "utils.hpp"

Algo::Algo() {
    benchmark = nullptr;
    population_size = 0;
}

int Algo::random_int(int min, int max) {
    return min + (rand() % (max - min + 1));
}

double Algo::random_double(double min, double max) {
    double r = (double)rand() / RAND_MAX;
    return min + (max - min) * r;
}

void Algo::set_func_number(int func_number) {
    this->func_number = func_number;
}