#include "ga.hpp"

GA::GA() {
    this->benchmark = new FOBenchmark();

    this->population_size = 50;
    this->iteration = 200000;

    crossover_rate = 0.99;
    mutation_rate = 0.01;
}

/**
 * Initializes the population for the Genetic Algorithm.
 * Randomly generates individuals within the specified bounds for each dimension.
 * Evaluates the fitness of each individual.
 * Sets the personal best and global best individuals and their corresponding fitness values.
 */
void GA::initialize_population() {
    for (int i = 0; i < population_size; i++) {
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            population[i][j] = random_double(benchmark->lower_bound[j], benchmark->upper_bound[j]);
        }
    }
    this->evaluate();

    // Initialize personal best and global best
    int best_index = min_element(this->fitness.begin(), this->fitness.end()) - this->fitness.begin();
    this->pbest = this->population[best_index];
    this->pbest_fitness = this->fitness;
    this->gbest = this->population[best_index];
    this->gbest_fitness = this->fitness[best_index];
}

void GA::intialize_data() {
    population = vector<vector<double>>(this->population_size, vector<double>(this->benchmark->dimentions));
    fitness = vector<double>(this->population_size);
    pbest = vector<double>(this->benchmark->dimentions);
    gbest = vector<double>(this->benchmark->dimentions);
    pbest_fitness = vector<double>(this->population_size);
    gbest_fitness = INT_MAX;
}

/**
 * Performs crossover operation on the population.
 * 
 * This function applies crossover operation on the population of individuals.
 * It randomly selects pairs of individuals and swaps their genetic material
 * beyond a randomly chosen point. The crossover operation is performed with a
 * probability defined by the crossover rate.
 */
// TODO: Special operators for function optimization
void GA::crossover() {
    int pbest_index = min_element(this->fitness.begin(), this->fitness.end()) - this->fitness.begin();
    vector<double> temp = population[pbest_index];
    for (int i = 0; i < population_size; i++) {
        if (random_double(0, 1) < crossover_rate) {
            int point = random_int(0, this->benchmark->dimentions);
            for (int j = point; j < this->benchmark->dimentions; j++) {
                population[i][j] = (population[i][j] + temp[j]) / 2;
            }
        }
    }

    // NOTE: This is a simple crossover operation. More advanced crossover operations can be implemented.
    // for (int i = 0; i < population_size; i += 2) {
    //     if (random_double(0, 1) < crossover_rate) {
    //         int point = random_int(0, this->benchmark->dimentions);
    //         for (int j = point; j < this->benchmark->dimentions; j++) {
    //             double temp = population[i][j];
    //             population[i][j] = population[i + 1][j];
    //             population[i + 1][j] = temp;
    //         }
    //     }
    // }
}

void GA::evaluate() {
    this->benchmark->cec17_test_func(population, this->fitness, this->benchmark->dimentions, this->population_size, this->func_number);
}

/**
 * Performs mutation on the population.
 * Randomly selects individuals from the population and mutates their genes.
 * The mutation is performed by randomly selecting a gene and replacing it with a new random value within the gene's bounds.
 */
void GA::mutation() {
    for (int i = 0; i < population_size; i++) {
        if (random_double(0, 1) < mutation_rate) {
            int point = random_int(0, this->benchmark->dimentions);
            population[i][point] = random_double(benchmark->lower_bound[point], benchmark->upper_bound[point]);
        }
    }
}

void GA::update_population() {
    crossover();
    mutation();

    this->evaluate();
}

void GA::update_global_best() {
    int best_index = min_element(this->fitness.begin(), this->fitness.end()) - this->fitness.begin();
    if (this->fitness[best_index] < this->gbest_fitness) {
        this->gbest = this->population[best_index];
        this->gbest_fitness = this->fitness[best_index];
    }
}

void GA::run() {

    intialize_data();

    initialize_population();

    for (int i = 0; i < iteration; i++) {
        update_population();

        update_global_best();
    
        // Print current best fitness value
        cout << "Iteration " << i + 1 << ": Best Fitness = " << gbest_fitness << endl;
    }
}

void GA::show_population() {
    for (int i = 0; i < population_size; i++) {
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            std::cout << population[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void GA::show_gbest() {
    for (int i = 0; i < this->benchmark->dimentions; i++) {
        std::cout << gbest[i] << " ";
    }
    std::cout << std::endl;
}