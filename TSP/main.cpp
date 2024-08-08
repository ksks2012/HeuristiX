#include "header.hpp"
#include "SA.hpp"
#include "node.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    // check the number of arguments
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " -algo <algorithm> -dataset <path_to_dataset>" << std::endl;
        return 1;
    }

    std::string algorithm;
    std::string dataset_path;

    // parse the arguments
    for (int i = 1; i < argc; i += 2) {
        std::string flag = argv[i];
        if (flag == "-algo") {
            algorithm = argv[i + 1];
        } else if (flag == "-dataset") {
            dataset_path = argv[i + 1];
        } else {
            std::cerr << "Unknown flag: " << flag << std::endl;
            return 1;
        }
    }

    // output the arguments
    std::cout << "Algorithm: " << algorithm << std::endl;
    std::cout << "Dataset path: " << dataset_path << std::endl;

    Algo *algo = nullptr;
    if (algorithm == "SA") {
        algo = new SA();
        string path(dataset_path);
        std::vector<Node> data = read_nodes(path);
        algo->set_data(data);
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << std::endl;
        return 1;
    }

    // run algorithm
    algo->run();

    // restore the result 
    
    return 0;
}
