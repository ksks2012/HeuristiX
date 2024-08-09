#ifndef TABU_SEARCH_HPP
#define TABU_SEARCH_HPP

#include "header.hpp"
#include "algo.hpp"

class TabuSearch : public Algo {
private:
    // Initialize tabu list
    vector<vector<int>> tabu_list;

    int max_iterations;
    int population_size;
public:
    // Initialize current solution
    vector<int> current_solution;

    // Initialize best solution
    vector<int> best_solution;

    double best_solution_cost;

private:
    void update_tabu_list(vector<vector<int>>& tabu_list, const vector<int>& solution);
    vector<vector<int>> generate_candidate_solutions(const vector<int>&);
    vector<int> select_next_solution(const vector<vector<int>>&, const vector<vector<int>>&);
public:
    TabuSearch();

    void run();
    double calculate_result(const vector<int>&);
};

#endif // TABU_SEARCH_HPP