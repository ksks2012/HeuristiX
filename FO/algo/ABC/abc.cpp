#include "abc.hpp"

ABC::ABC() {
    this->benchmark = new FOBenchmark();

    this->population_size = 50;
    this->iteration = 20000;

    limit_trail = 100;
}

ABC::ABC(YAML::Node config_node) {
    try {
        this->benchmark = new FOBenchmark();

        YAML::Node global_config_node = config_node["Global"];

        // Set population size from config_node
        if (global_config_node["population_size"]) {
            this->population_size = global_config_node["population_size"].as<int>();
        } else {
            throw std::runtime_error("Population size not specified in config_node.");
        }

        // Set iteration from config_node
        if (global_config_node["iteration"]) {
            this->iteration = global_config_node["iteration"].as<int>();
        } else {
            throw std::runtime_error("Iteration not specified in config_node.");
        }

        YAML::Node abc_config_node = config_node["ABC"];

        if (abc_config_node["limit_trail"]) {
            this->limit_trail = abc_config_node["limit_trail"].as<int>();
        } else {
            throw std::runtime_error("limit_trail not specified in config_node.");
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}


/**
 * Initializes the data for the Artificial Bee Colony (ABC) algorithm.
 */
void ABC::intialize_data() {
    population = vector<vector<double>>(this->population_size, vector<double>(this->benchmark->dimentions));
    fitness = vector<double>(this->population_size);
    pbest = vector<double>(this->benchmark->dimentions);
    gbest = vector<double>(this->benchmark->dimentions);
    pbest_fitness = vector<double>(this->population_size);
    gbest_fitness = INT_MAX;

    // // ABC local data
    trails = vector<int>(this->population_size, 0);
    probability_list = vector<double>(this->population_size);
}

/**
 * Initializes the particles for the Artificial Bee Colony (ABC) algorithm.
 */
void ABC::initialize_particles() {
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

/**
 * Calculates the honey source value based on the given input value.
 *
 * @param value The input value.
 * @return The calculated honey source value.
 */
double ABC::cal_honey_source(double value) {
    double honey_source = 0.0;
    // NOTE: The positive and negative distribution of values ​​is not a normal distribution
    if (value >= 0) {
        honey_source = 1.0 / (1.0 + value);
    } else {
        honey_source = 1.0 + abs(value);
    }

    return honey_source;
}

// Build probability list
void ABC::build_probability_list() {
    vector<double> out(population_size, 0.0);
    for(int i = 0; i < population_size; i++) {
        out[i] = cal_honey_source(fitness[i]);
    }

    double out_sum = accumulate(out.begin(), out.end(), 0.0);
    for (int i = 0; i < population_size; i++) {
        probability_list[i] = out[i] / out_sum;
    }
}

/**
 * The employed_bees function performs the employed bee phase of the Artificial Bee Colony (ABC) algorithm.
 * It updates the population by generating new solutions based on the current population.
 * Each employed bee selects a random solution from the population and modifies one dimension of it using a formula.
 * The modified solution is then evaluated and compared with the corresponding personal best solution.
 * If the modified solution has a better fitness value, it becomes the new personal best solution.
 * Otherwise, a trail counter is incremented to keep track of unsuccessful modifications.
 * This function updates the personal best solutions and trail counters for each employed bee.
 */
void ABC::employed_bees() {
    for(int i = 0; i < population_size; i++) {
        int index = random_int(0, this->population_size - 1);
        int point = random_int(0, this->benchmark->dimentions);
        population[index][point] = population[i][point] + random_double(-1, 1) * (population[i][point] - population[index][point]);
    }

    this->evaluate();
    for(int i = 0; i < population_size; i++) {
        if(fitness[i] < pbest_fitness[i]) {
            pbest_fitness[i] = fitness[i];
            pbest = population[i];
            trails[i] = 0;
        } else {
            trails[i]++;
        }
    }
}

/**
 * The onlooker_bees function is responsible for the onlooker bees phase in the ABC algorithm.
 * It selects onlooker bees based on their probability and updates their positions in the population.
 * After updating the positions, it evaluates the fitness of the population and updates the personal best fitness and trails.
 */
void ABC::onlooker_bees() {
    build_probability_list();
    for(int i = 0; i < population_size; i++) {
        if (random_double(0, 1) > probability_list[i]) {
            continue;
        }
        int index = RWS();    
        int point = random_int(0, this->benchmark->dimentions);
        population[index][point] = population[i][point] + random_double(-1, 1) * (population[i][point] - population[index][point]);
    }

    this->evaluate();
    for(int i = 0; i < population_size; i++) {
        if(fitness[i] < pbest_fitness[i]) {
            pbest_fitness[i] = fitness[i];
            pbest = population[i];
            trails[i] = 0;
        } else {
            trails[i]++;
        }
    }
}

/**
 * Scout bees in the ABC algorithm.
 * 
 * This function checks the trails of each bee in the population and if a trail exceeds the limit,
 * the bee is considered a scout. The scout bee then generates a new solution by randomly selecting
 * values within the lower and upper bounds of each dimension. The trail count is reset to zero for
 * the scout bee.
 */
void ABC::scout_bees() {
    for(int i = 0; i < population_size; i++) {
        if(trails[i] > limit_trail) {
            for(int j = 0; j < this->benchmark->dimentions; j++) {
                population[i][j] = random_double(this->benchmark->lower_bound[j], this->benchmark->upper_bound[j]);
            }
            trails[i] = 0;
        }
    }
}

/**
 * Updates the particles in the ABC algorithm.
 */
void ABC::update_particles() {
    // Employed Bees Phase
    employed_bees();

    // Onlooker Bees Phase
    onlooker_bees();

    // Scout Bees Phase
    scout_bees();
}

/**
 * Updates the global best position in the Artificial Bee Colony (ABC) algorithm.
 */
void ABC::update_global_best() {
    int best_index = min_element(this->fitness.begin(), this->fitness.end()) - this->fitness.begin();
    if (this->fitness[best_index] < this->gbest_fitness) {
        this->gbest = this->population[best_index];
        this->gbest_fitness = this->fitness[best_index];
    }
}

void ABC::run() {
    cout << "ABC" << endl;
    
    std::cout << scientific << setprecision(8);

    // Initialize particles
    initialize_particles();

    // Run ABC iterations
    for (int i = 0; i < this->iteration; i++) {
        // Update particle positions and velocities
        update_particles();

        // Update global best position
        update_global_best();

        // Print current best fitness value
        cout << "Iteration " << i + 1 << ": Best Fitness = " << gbest_fitness << endl;
    }
}