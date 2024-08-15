#include "gwo.hpp"

GWO::GWO() {
    // default constructor
    this->benchmark = new FOBenchmark();

    this->population_size = 50;
    this->max_evaluation = 20000;

    a = 2.0;
    c = 2.0;
}

GWO::GWO(YAML::Node config_node) {
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

        YAML::Node gwo_config_node = config_node["GWO"];
        if (gwo_config_node["a"]) {
            this->a = gwo_config_node["a"].as<double>();
        } else {
            throw std::runtime_error("Iteration not specified in config_node.");
        }

        if (gwo_config_node["c"]) {
            this->c = gwo_config_node["c"].as<double>();
        } else {
            throw std::runtime_error("Iteration not specified in config_node.");
        }

        // TODO: args for GWO

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}

void GWO::intialize_data() {
    population = vector<vector<double>>(this->population_size, vector<double>(this->benchmark->dimentions));
    fitness = vector<double>(this->population_size);
    pbest = vector<double>(this->benchmark->dimentions);
    gbest = vector<double>(this->benchmark->dimentions);
    pbest_fitness = vector<double>(this->population_size);
    gbest_fitness = INT_MAX;

    // GWO local data
    alpha = vector<double>(this->benchmark->dimentions);
    beta = vector<double>(this->benchmark->dimentions);
    delta = vector<double>(this->benchmark->dimentions);
    alpha_index = 0;
    beta_index = 0;
    delta_index = 0;
}

void GWO::initialize_population() {
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
    vector<int> indices(this->fitness.size());
    iota(indices.begin(), indices.end(), 0); // Fill with 0, 1, ..., fitness.size()-1

    // Sort indices based on fitness values
    sort(indices.begin(), indices.end(), [this](int a, int b) {
        return this->fitness[a] < this->fitness[b];
    });;

    // Save top three indices
    this->alpha_index = indices[0];
    this->beta_index = indices[1];
    this->delta_index = indices[2];

    // Set global best
    this->gbest = this->population[this->alpha_index];
    this->gbest_fitness = this->fitness[this->alpha_index];
}


inline double GWO::cal_A() {
    return a * (2 * random_double(0, 1) - 1);
}

inline double GWO::cal_C() {
    return c * random_double(0, 1);
}

void GWO::encircling_prey() {
    for (int i = 0; i < this->population_size; i++) {
        // D = ∣C⋅Xp​(t) − X(t)∣
        vector<double> D(this->benchmark->dimentions);
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            D[j] = abs(cal_C() * gbest[j] - this->population[i][j]);
        }

        // X(t+1) = Xp​(t) − A⋅D
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            this->population[i][j] = this->population[this->alpha_index][j] - cal_A() * D[j];
        }
    }
}

void GWO::hunting() {
    // X_(t+1) = 1/3⋅​(Xα​ + Xβ​ + Xδ​)
    for (int i = 0; i < this->population_size; i++) {
        // D = ∣C⋅Xp​(t) − X(t)∣
        // X(t+1) = Xp​(t) − A⋅D
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            double x_alpha = this->population[this->alpha_index][j] - cal_A() * (cal_C() * this->population[this->alpha_index][j] - this->population[i][j]);
            double x_beta = this->population[this->beta_index][j] - cal_A() * (cal_C() * this->population[this->beta_index][j] - this->population[i][j]);
            double x_delta = this->population[this->delta_index][j] - cal_A() * (cal_C() * this->population[this->delta_index][j] - this->population[i][j]);

            this->population[i][j] = (x_alpha + x_beta + x_delta) / 3;
        }
    }
}

void GWO::update_population() {
    encircling_prey();
    hunting();    

    this->evaluate();
}

void GWO::update_global_best() {
    // Initialize personal best and global best
    vector<int> indices(this->fitness.size());
    iota(indices.begin(), indices.end(), 0); // Fill with 0, 1, ..., fitness.size()-1

    // Sort indices based on fitness values
    sort(indices.begin(), indices.end(), [this](int a, int b) {
        return this->fitness[a] < this->fitness[b];
    });;

    // Save top three indices
    this->alpha_index = indices[0];
    this->beta_index = indices[1];
    this->delta_index = indices[2];

    // Set global best
    if (this->fitness[this->alpha_index] < this->gbest_fitness) {
        this->gbest = this->population[this->alpha_index];
        this->gbest_fitness = this->fitness[this->alpha_index];
    }

    update_weights();
}

void GWO::update_weights() {
    // a decreases linearly from 2 to 0
    a = 2 - evaluation_count * (2 / (double)this->max_evaluation);
}