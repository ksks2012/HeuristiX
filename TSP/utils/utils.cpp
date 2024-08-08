#include "utils.hpp"

std::vector<Node> read_nodes(string &dataset_path) {
    std::string line;
    std::vector<Node> nodes;

    std::ifstream inputFile(dataset_path);
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return nodes;
    }

    while (std::getline(inputFile, line)) {
        // TODO: Restore size and malloc nodes
        if (line == "NODE_COORD_SECTION") {
            while (std::getline(inputFile, line) && line != "EOF") {
                std::istringstream iss(line);
                Node node;
                iss >> node.index >> node.x >> node.y;
                nodes.push_back(node);
            }
            break;
        }
    }

    inputFile.close();

    // Output the nodes for verification
    for (const auto& node : nodes) {
        std::cout << "Index: " << node.index << ", X: " << node.x << ", Y: " << node.y << std::endl;
    }

    return nodes;
}

double calculate_distance(const Node& node1, const Node& node2) {
    double dx = node1.x - node2.x;
    double dy = node1.y - node2.y;
    return sqrt(dx * dx + dy * dy);
}