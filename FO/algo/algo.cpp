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


/**
 * Selects an individual from the population using Roulette Wheel Selection (RWS) algorithm.
 * 
 * @return The index of the selected individual.
 */
int Algo::RWS() {
    double sum = 0;
    for (int i = 0; i < population_size; i++) {
        sum += fitness[i];
    }

    double r = random_double(0, sum);
    double partial_sum = 0;
    for (int i = 0; i < population_size; i++) {
        partial_sum += fitness[i];
        if (partial_sum >= r) {
            return i;
        }
    }

    return 0;
}

void Algo::show_population() {
    for (int i = 0; i < this->population_size; i++) {
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            cout << this->population[i][j] << " ";
        }
        cout << endl;
    }
}

void Algo::show_gbest() {
    for (int i = 0; i < this->benchmark->dimentions; i++) {
        cout << this->gbest[i] << " ";
    }
    cout << endl;
}

void Algo::evaluate() {
    this->benchmark->cec17_test_func(population, this->fitness, this->benchmark->dimentions, this->population_size, this->func_number);
    this->evaluation_count += this->population_size;
}

void Algo::run() {
    std::cout << scientific << setprecision(8);

    intialize_data();

    initialize_population();

    while(evaluation_count < max_evaluation) {
        update_population();

        update_global_best();
        
        // Print best fitness value
        cout << "Iteration " << evaluation_count + 1 << ": Best Fitness = " << gbest_fitness << endl;
    }
    // Print best fitness value
    cout << "Iteration " << evaluation_count + 1 << ": Best Fitness = " << gbest_fitness << endl;
}