#include "header.hpp"
#include "SA.hpp"
#include "tabu_search.hpp"
#include "node.hpp"
#include "utils.hpp"

/* print a description of all supported options */
void usage(ostream &os, const string &path) {
    /* take only the last portion of the path */
    string basename = path.substr(path.find_last_of('/') + 1);

    os << "usage: " << basename << " [OPTION]\n"
        << "[Help options]:\n"
        << "  -h, --help\t\t"
        << "Print this help and exit.\n"
        << "[Necessary paramters]:\n"
        << "  -a, --algo=STRING\t"
        << "Choose the algorithm to run.\n"
        << "  -d, --dataset=STRING\t"
        << "Choose the file path of dataset.\n";
}

int main(int argc, char* argv[]) {
    string algorithm;
    string dataset_path;

    bool help_flag = false;
    int opt;

    /* no_argument: means that the option does not take an argument
     * optional_argument: means that the option may or may not take an argument
     * required_argument: means that the option requires an argument
      */
    struct option longopts[] = {
        {"help", no_argument, nullptr, 'h'},
        {"algo", required_argument, nullptr, 'a'},
        {"dataset", required_argument, nullptr, 'd'},
        {0}
    };

    while (true) {
        opt = getopt_long(argc, argv, "hf::m:", longopts, nullptr);

        if (opt == -1) {
            break;
        }

        switch (opt) {
            case 'h':
                help_flag = true;
                break;
            case 'a':
                algorithm = optarg;
                break;
            case 'd':
                dataset_path = optarg;
                break;
            case '?':
                usage(cerr, argv[0]);
                return 1;
            default:
                break;
        }
    }

    if (help_flag) {
        usage(cout, argv[0]);
        return 0;
    }

    if(algorithm.empty() || dataset_path.empty()) {
        usage(cerr, argv[0]);
        cerr << "Missing arguments" << endl;
        return 1;
    }

    // output the arguments
    cout << "Algorithm: " << algorithm << endl;
    cout << "Dataset path: " << dataset_path << endl;

    Algo *algo = nullptr;
    if (algorithm == "SA") {
        algo = new SA();
    } else if (algorithm == "TABU") {
        algo = new TabuSearch();
    } else {
        cerr << "Unknown algorithm: " << algorithm << endl;
        return 1;
    }

    // Read the dataset
    string path(dataset_path);
    vector<Node> data = read_nodes(path);
    algo->set_data(data);

    // run algorithm
    algo->run();

    // restore the result 
    
    return 0;
}
