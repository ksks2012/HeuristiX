#include "pso.hpp"

PSO::PSO() {
    this->benchmark = new FOBenchmark();

    // TODO: config setting
    this->population_size = 50;
    this->iteration = 20000;

    // NOTE: w from w_max to w_min by iteration
    this->w = 0.75;
    this->c1 = 1.5;
    this->c2 = 1.5;
    // for vmax
    this->vrate = 0.2;
}

/**
 * Initializes the data for the Particle Swarm Optimization (PSO) algorithm.
 */
void PSO::intialize_data() {
    population = vector<vector<double>>(this->population_size, vector<double>(this->benchmark->dimentions));
    velocity = vector<vector<double>>(this->population_size, vector<double>(this->benchmark->dimentions));
    fitness = vector<double>(this->population_size);
    pbest = vector<double>(this->benchmark->dimentions);
    gbest = vector<double>(this->benchmark->dimentions);
    pbest_fitness = vector<double>(this->population_size);
    gbest_fitness = INT_MAX;

    vmax = vector<double>(this->benchmark->dimentions, 0);
    vmin = vector<double>(this->benchmark->dimentions, 0);
}

/**
 * Initializes the particles for the Particle Swarm Optimization (PSO) algorithm.
 * 
 * This function initializes the population, velocity, fitness, personal best, and global best
 * for the PSO algorithm. It generates random particles within the specified bounds and evaluates
 * their fitness using the benchmark function. The personal best and global best are also initialized
 * based on the initial population.
 */
void PSO::initialize_particles() {
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

    // Initialize velocity
    for (int i = 0; i < this->population_size; i++) {
        vector<double> v(this->benchmark->dimentions);
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            v[j] = 0.0;
            vmax[j] = vrate * this->benchmark->upper_bound[j];
            vmin[j] = vrate * this->benchmark->lower_bound[j];
        }
        this->velocity[i] = v;
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
 * Updates the particles in the PSO algorithm.
 */
void PSO::update_particles() {
    // Update particle positions based on velocity
    for (int i = 0; i < this->population_size; i++) {
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            this->velocity[i][j] = w * this->velocity[i][j] + c1 * random_double(0, 1) * (this->pbest[j] - this->population[i][j]) + c2 * random_double(0, 1) * (this->gbest[j] - this->population[i][j]);
            this->population[i][j] += this->velocity[i][j];
            
            // check bounds of velocity -> vmax, vmin
            if (this->velocity[i][j] > this->vmax[j] || this->velocity[i][j] < this->vmin[j]) {
                this->velocity[i][j] = random_double(this->vmax[j], this->vmin[j]);
            }

            // check bounds
            if (this->population[i][j] < this->benchmark->lower_bound[j] || this->population[i][j] > this->benchmark->upper_bound[j]) {
                this->population[i][j] = random_double(this->benchmark->lower_bound[j], this->benchmark->upper_bound[j]);
            }
        }
    }
    this->evaluate();
    int best_index = min_element(this->fitness.begin(), this->fitness.end()) - this->fitness.begin();
    this->pbest = this->population[best_index];
    this->pbest_fitness = this->fitness;
}

/**
 * Updates the global best position in the Particle Swarm Optimization (PSO) algorithm.
 */
void PSO::update_global_best() {
    int best_index = min_element(this->fitness.begin(), this->fitness.end()) - this->fitness.begin();
    if (this->fitness[best_index] < this->gbest_fitness) {
        this->gbest = this->population[best_index];
        this->gbest_fitness = this->fitness[best_index];
    }
}

void PSO::run() {
    cout << "PSO" << endl;
    
    std::cout << scientific << setprecision(8);

    // Initialize particles
    initialize_particles();

    // Run PSO iterations
    for (int i = 0; i < this->iteration; i++) {
        // Update particle positions and velocities
        update_particles();

        // Update global best position
        update_global_best();

        // Print current best fitness value
        cout << "Iteration " << i + 1 << ": Best Fitness = " << gbest_fitness << endl;
    }
}

void PSO::evaluate() {
    this->benchmark->cec17_test_func(population, this->fitness, this->benchmark->dimentions, this->population_size, this->func_number);
}

void PSO::show_population() {
    for (int i = 0; i < this->population_size; i++) {
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            cout << this->population[i][j] << " ";
        }
        cout << endl;
    }
}

void PSO::show_velocity() {
    for (int i = 0; i < this->population_size; i++) {
        for (int j = 0; j < this->benchmark->dimentions; j++) {
            cout << this->velocity[i][j] << " ";
        }
        cout << endl;
    }
}

void PSO::show_gbest() {
    for (int i = 0; i < this->benchmark->dimentions; i++) {
        cout << this->gbest[i] << " ";
    }
    cout << endl;
}