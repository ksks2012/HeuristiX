#include "SA.hpp"
#include "utils.hpp"

SA::SA() {
        std::cout << "Simulated Annealing" << std::endl;
    }

void SA::set_data(std::vector<Node> &data) {
    std::cout << "Setting data" << std::endl;
    this->data = data;

    // Set the node size
    this->node_size = this->data.size();
    std::cout << "this->node_size " << this->node_size << std::endl;
}

void SA::run() {
    std::cout << "Running SA" << std::endl;

    this->calculate_distance_table();

    // Initialize the current solution
    std::vector<Node> current_solution = this->data;
    std::random_shuffle(current_solution.begin(), current_solution.end());
    
    // TODO: Change to etc/config
    // Set the initial temperature and cooling rate
    double temperature = 100.0;
    double cooling_rate = 0.99;
    
    // Initialize the best solution
    std::vector<Node> best_solution = current_solution;
    double best_distance = calculate_result(best_solution);
    
    int iter = 0;
    // Perform SA iterations
    while (temperature > 1.0) {
        // Generate a new solution by applying a random swap
        std::vector<Node> new_solution = current_solution;
        this->random_switch(new_solution);

        // Calculate the new solution's distance
        double new_distance = calculate_result(new_solution);
        
        // Decide whether to accept the new solution
        double prob = acceptance_probability(best_distance, new_distance, temperature);
        if (prob > (double)rand() / RAND_MAX) {
            current_solution = new_solution;
            
            // Update the best solution if necessary
            if (new_distance < best_distance) {
                best_solution = current_solution;
                best_distance = new_distance;
            }
        }

        cout << "iter: " << iter << " " << best_distance << " " << prob << endl;
        
        // Cool down the temperature
        temperature *= cooling_rate;
        iter++;
    }
    
    // Print the best solution
    std::cout << "Best Solution: ";
    for (const Node& node : best_solution) {
        std::cout << node.index << " ";
    }
    std::cout << std::endl;
    cout << best_distance << endl;
}

double SA::calculate_result(const std::vector<Node>& solution) {
    double distance = 0.0;
    for (int i = 0; i < this->node_size - 1; i++) {
        distance += get_distance_table(solution[i].index, solution[i + 1].index);
    }
    distance += get_distance_table(solution.back().index, solution.front().index);
    return distance;
}

double SA::acceptance_probability(double current_distance, double new_distance, double temperature) {
    if (new_distance < current_distance) {
        return 1.0;
    }
    return exp((current_distance - new_distance) / temperature);
}