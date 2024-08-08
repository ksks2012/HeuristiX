#include "algo.hpp"
#include "utils.hpp"

Algo::Algo() {
    ;
}

void Algo::calculate_distance_table() {
    std::cout << "Calculating distance table" << std::endl;
    this->distance.resize(this->data.size(), std::vector<double>(this->data.size()));
    for (int i = 0; i < this->data.size(); i++) {
        for (int j = 0; j < this->data.size(); j++) {
            if(i == j) {
                this->distance[i][j] = 0.0;
                continue;
            }
            this->distance[i][j] = calculate_distance(this->data[i], this->data[j]);
        }
    }
}

double Algo::get_distance_table(int x, int y) {
    return this->distance[x - 1][y - 1];
}

void Algo::two_opt(std::vector<Node>& path) {
    bool improvement = true;

    while(improvement) {
        improvement = false;
        for (int i = 0; i < this->node_size - 1; ++i) {
            for (int j = i + 2; j < this->node_size; ++j) {
                double old_dist = get_distance_table(path[i].index, path[i + 1].index) +
                                  get_distance_table(path[j].index, path[(j + 1) % this->node_size].index);
                double new_dist = get_distance_table(path[i].index, path[j].index) +
                                  get_distance_table(path[i + 1].index, path[(j + 1) % this->node_size].index);

                if (new_dist < old_dist) {
                    std::reverse(path.begin() + i + 1, path.begin() + j + 1);
                    improvement = true;
                }
            }
        }
    }
}

void Algo::three_opt(std::vector<Node>& path) {
    bool improvement = true;

    while(improvement) {
        improvement = false;

        // Iterate over three indices i, j, k
        for (int i = 0; i < this->node_size - 3; ++i) {
            for (int j = i + 2; j < this->node_size - 1; ++j) {
                for (int k = j + 2; k < this->node_size + (i > 0); ++k) {

                    // Store the original distance
                    double original_distance = get_distance_table(path[i].index, path[i + 1].index) +
                                               get_distance_table(path[j].index, path[j + 1].index) +
                                               get_distance_table(path[k % this->node_size].index, path[(k + 1) % this->node_size].index);

                    // Try different 3-opt rearrangements
                    std::vector<std::vector<Node>> possible_paths;

                    // Keep all segments in order
                    possible_paths.push_back(path);

                    // Reverse the middle segment
                    std::vector<Node> new_path1 = path;
                    std::reverse(new_path1.begin() + i + 1, new_path1.begin() + j + 1);
                    possible_paths.push_back(new_path1);

                    // Reverse the last segment
                    std::vector<Node> new_path2 = path;
                    std::reverse(new_path2.begin() + j + 1, new_path2.begin() + k + 1);
                    possible_paths.push_back(new_path2);

                    // Reverse the middle and last segments
                    std::vector<Node> new_path3 = path;
                    std::reverse(new_path3.begin() + i + 1, new_path3.begin() + k + 1);
                    possible_paths.push_back(new_path3);

                    // Reverse the first and last segments
                    std::vector<Node> new_path4 = path;
                    std::reverse(new_path4.begin() + i + 1, new_path4.begin() + j + 1);
                    std::reverse(new_path4.begin() + j + 1, new_path4.begin() + k + 1);
                    possible_paths.push_back(new_path4);

                    // Find the best rearrangement
                    for (auto& p : possible_paths) {
                        double new_distance = get_distance_table(p[i].index, p[i + 1].index) +
                                              get_distance_table(p[j].index, p[j + 1].index) +
                                              get_distance_table(p[k % this->node_size].index, p[(k + 1) % this->node_size].index);

                        if (new_distance < original_distance) {
                            path = p;
                            improvement = true;
                            break;
                        }
                    }

                    if (improvement) {
                        break;
                    }
                }
                if (improvement) {
                    break;
                }
            }
            if (improvement) {
                break;
            }
        }
    }
}

void Algo::random_switch(std::vector<Node>& path) {
    int i = rand() % this->node_size;
    int j = rand() % this->node_size;
    std::swap(path[i], path[j]);
}