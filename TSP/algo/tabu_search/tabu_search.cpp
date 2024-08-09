#include "tabu_search.hpp"

TabuSearch::TabuSearch() {
    cout << "Tabu Search" << endl;
    // TODO: Change to etc/config
    this->max_iterations = 10000;
    this->population_size = 10;

    // Initialize best solution cost
    this->best_solution_cost = numeric_limits<double>::max();
}

void TabuSearch::update_tabu_list(vector<vector<int>>& tabu_list, const vector<int>& solution) {
    // Add the solution to the tabu list
    tabu_list.push_back(solution);

    // Remove the oldest solution from the tabu list if it exceeds the maximum size
    if (tabu_list.size() > 10) {
        tabu_list.erase(tabu_list.begin());
    }
}

vector<int> TabuSearch::select_next_solution(const vector<vector<int>>& candidate_solutions, const vector<vector<int>>& tabu_list) {
    // Select the best candidate solution that is not in the tabu list
    vector<int> best_solution;
    double best_solution_cost = numeric_limits<double>::max();

    for (const auto& candidate : candidate_solutions) {
        // Check if the candidate solution is in the tabu list
        if (find(tabu_list.begin(), tabu_list.end(), candidate) == tabu_list.end()) {
            // double candidate_cost = evaluate_solution(candidate);
            double candidate_cost = calculate_result(candidate);

            // Check if the candidate solution is better than the current best solution
            if (candidate_cost < best_solution_cost) {
                best_solution = candidate;
                best_solution_cost = candidate_cost;
            }
        }
    }

    return best_solution;
}

vector<vector<int>> TabuSearch::generate_candidate_solutions(const vector<int>& current_solution) {
    // Generate new candidate solutions
    vector<vector<int>> candidate_solutions(population_size);

    for(int i = 0; i < population_size; i++) {
        vector<int> candidate_solution = current_solution;
        random_shuffle(candidate_solution.begin(), candidate_solution.end());
        candidate_solutions[i] = candidate_solution;
    }

    return candidate_solutions;
}

void TabuSearch::run() {
    // implement the tabu search algorithm here
    cout << "Tabu search algorithm is running..." << endl;

    this->calculate_distance_table();

    // Initialize current solution
    this->current_solution.resize(node_size);
    iota(this->current_solution.begin(), this->current_solution.end(), 1);
    random_shuffle(this->current_solution.begin(), this->current_solution.end());
    
    this->best_solution = this->current_solution;
    this->best_solution_cost = calculate_result(this->current_solution);

    // Initialize iteration counter
    int iteration = 0;

    // Start tabu search algorithm
    while (iteration < max_iterations) {
        // Generate new candidate solutions
        vector<vector<int>> candidate_solutions = this->generate_candidate_solutions(this->current_solution);

        // Evaluate candidate solutions
        for (const auto& candidate : candidate_solutions) {
            double candidate_cost = this->calculate_result(candidate);

            // Check if candidate solution is better than the current best solution
            if (candidate_cost < best_solution_cost) {
                best_solution = candidate;
                best_solution_cost = candidate_cost;
            }
        }

        // Update current solution
        this->current_solution = this->select_next_solution(candidate_solutions, tabu_list);

        // Update tabu list
        this->update_tabu_list(tabu_list, current_solution);

        // Increment iteration counter
        iteration++;
        cout << "Iteration: " << iteration << " Best solution cost: " << best_solution_cost << endl;
    }

    // Print best solution
    cout << "Best solution found: ";
    for (const auto& city : best_solution) {
        cout << city << " ";
    }
    cout << endl;

    // Print best solution cost
    cout << "Best solution cost: " << best_solution_cost << endl;
}

double TabuSearch::calculate_result(const vector<int>& solution) {
    double distance = 0.0;
    for (int i = 0; i < solution.size() - 1; i++) {
        distance += get_distance_table(solution[i], solution[i + 1]);
    }
    distance += get_distance_table(solution.back(), solution.front());
    return distance;
}