#include "woa.hpp"

WOA::WOA() {
    // default constructor
    this->benchmark = new FOBenchmark();

    this->population_size = 50;
    this->max_evaluation = 20000;

    a = 2.0;
    c = 2.0;
}

WOA::WOA(YAML::Node config_node) {
    try {
        this->benchmark = new FOBenchmark();

        YAML::Node global_config_node = config_node["Global"];

        // Set population size from config_node
        if (global_config_node["population_size"]) {
            this->population_size = global_config_node["population_size"].as<int>();
        } else {
            throw std::runtime_error("Population size not specified in config_node.");
        }

        // Set max_evaluation from config_node
        if (global_config_node["evaluation"]) {
            this->max_evaluation = global_config_node["evaluation"].as<int>();
        } else {
            throw std::runtime_error("Iteration not specified in config_node.");
        }

        YAML::Node woa_config_node = config_node["WOA"];
        if (woa_config_node["a"]) {
            this->a = woa_config_node["a"].as<double>();
        } else {
            throw std::runtime_error("Iteration not specified in config_node.");
        }

        if (woa_config_node["c"]) {
            this->c = woa_config_node["c"].as<double>();
        } else {
            throw std::runtime_error("Iteration not specified in config_node.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}

void WOA::intialize_data() {
    population = vector<vector<double>>(this->population_size, vector<double>(this->benchmark->dimentions));
    fitness = vector<double>(this->population_size);
    pbest = vector<double>(this->benchmark->dimentions);
    gbest = vector<double>(this->benchmark->dimentions);
    pbest_fitness = vector<double>(this->population_size);
    gbest_fitness = INT_MAX;

    // local data for WOA
    D = vector<vector<double>>(this->population_size, vector<double>(this->benchmark->dimentions));
}

void WOA::initialize_population() {
    // Initialize population
    for (int i = 0; i < this->population_size; i++) {
        vector<double> particle(this->benchmark->dimentions);
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            assert(benchmark->lower_bound.size() > size_t(j) || benchmark->lower_bound.size() == 0); // Debugging assertion
            assert(benchmark->upper_bound.size() > size_t(j) || benchmark->upper_bound.size() == 0); // Debugging assertion
            particle[j] = random_double(this->benchmark->lower_bound[j], this->benchmark->upper_bound[j]);
        }
        this->population[i] = particle;
    }

    // Initialize fitness
    this->evaluate();

    // Initialize personal best and global best
    int best_index = min_element(this->fitness.begin(), this->fitness.end()) - this->fitness.begin();
    this->pbest = this->population[best_index];
    this->pbest_fitness = this->fitness;
    this->gbest = this->population[best_index];
    this->gbest_fitness = this->fitness[best_index];
}

inline double WOA::cal_A() {
    return a * (2 * random_double(0, 1) - 1);
}

inline double WOA::cal_C() {
    return c * random_double(0, 1);
}

void WOA::encircling_prey() {
    for (int i = 0; i < this->population_size; i++) {
        // D = ∣C⋅Xp​(t) − X(t)∣
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            D[i][j] = abs(cal_C() * gbest[j] - this->population[i][j]);
        }

        // X(t+1) = Xp​(t) − A⋅D
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            this->population[i][j] = gbest[j] - cal_A() * D[i][j];
        }
    }
}

void WOA::spiral_updating() {
    // X(t+1) =D′⋅e^bl⋅cos(2πl) + X(t)
    for (int i = 0; i < this->population_size; i++) {
        double b = random_double(0, 2);
        double l = random_double(-1, 1);

        for (int j = 0; j < this->benchmark->dimentions; j++) {
            this->population[i][j] = D[i][j] * exp(b * l) * cos(2 * M_PI * l) + this->population[i][j];
        }
    }
}

void WOA::exploration() {
    for (int i = 0; i < this->population_size; i++) {
        // D = ∣C⋅X_rand​​(t) − X(t)∣
        int rand_index = random_int(0, this->population_size - 1);
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            D[i][j] = abs(cal_C() * this->population[rand_index][j] - this->population[i][j]);
        }

        // X(t+1) = X_rand​(t) − A⋅D
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            this->population[i][j] = this->population[rand_index][j] - cal_A() * D[i][j];
        }
    }
}

void WOA::update_global_best() {
    int best_index = min_element(this->fitness.begin(), this->fitness.end()) - this->fitness.begin();
    if (this->fitness[best_index] < this->gbest_fitness) {
        this->gbest = this->population[best_index];
        this->gbest_fitness = this->fitness[best_index];
    }
    
    update_weights();
}

void WOA::update_weights() {
    // a decreases linearly from 2 to 0
    a = 2 - evaluation_count * (2 / (double)this->max_evaluation);
}

void WOA::update_population() {
    encircling_prey();
    spiral_updating();
    exploration();

    this->evaluate();
}

