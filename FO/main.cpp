#include "ga.hpp"
#include "header.hpp"
#include "pso.hpp"
#include "utils.hpp"


/* print a description of all supported options */
void usage(std::ostream &os, const std::string &path) {
    /* take only the last portion of the path */
    std::string basename = path.substr(path.find_last_of('/') + 1);

    os << "usage: " << basename << " [OPTION]\n"
        << "[Help options]:\n"
        << "  -h, --help\t\t"
        << "Print this help and exit.\n"
        << "[Necessary paramters]:\n"
        << "  -a, --algo=STRING\t"
        << "Choose the algorithm to run.\n"
        << "  -f, --func=STRING\t"
        << "Choose the benchmark function number to run.\n"
        << "  -d, --dim=STRING\t"
        << "Choose the number of dimentions.\n"
        << "  -c, --conf=STRING\t"
        << "Choose the config file.\n";
}

int main(int argc, char* argv[]) {
    string algorithm;
    string function_number;
    string dimentions;
    string config_file;

    bool help_flag = false;
    int opt;

    
    /* no_argument: means that the option does not take an argument
     * optional_argument: means that the option may or may not take an argument
     * required_argument: means that the option requires an argument
      */
    struct option longopts[] = {
        {"help", no_argument, nullptr, 'h'},
        {"algo", required_argument, nullptr, 'a'},
        {"func", required_argument, nullptr, 'f'},
        {"dim", required_argument, nullptr, 'd'},
        {"conf", required_argument, nullptr, 'c'},
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
            case 'f':
                function_number = optarg;
                break;
            case 'd':
                dimentions = optarg;
                break;
            case 'c':
                config_file = optarg;
                break;
            case '?':
                usage(std::cerr, argv[0]);
                return 1;
            default:
                break;
        }
    }

    if (help_flag) {
        usage(cout, argv[0]);
        return 0;
    }

    if(config_file.empty() || algorithm.empty() || function_number.empty() || dimentions.empty()) {
        usage(cout, argv[0]);
        cerr << "Error: Missing arguments" << endl;
        return 1;
    }

    YAML::Node config_node;
    try {
         config_node = YAML::LoadFile(config_file);
    } catch (const std::invalid_argument &e) {
        cerr << "Error: Missing config file" << endl;
        return 1;
    }

    // output the arguments
    cout << "Algorithm: " << algorithm << endl;
    cout << "Function Number: " << function_number << endl;
    cout << "Dimentions: " << dimentions << endl;

    // TODO: better random method
    // initialize random seed
    srand(time(0));

    Algo *algo = nullptr;
    if (algorithm == "PSO") {
        algo = new PSO(config_node);
    } else if (algorithm == "GA") {
        algo = new GA(config_node);
    } else {
        cerr << "Unknown algorithm: " << algorithm << endl;
        return 1;
    }

    // Set evaluation function
    algo->benchmark->set_dimensions(stoi(dimentions));
    algo->benchmark->set_bounds(stoi(function_number), stoi(dimentions));

    algo->set_func_number(stoi(function_number));
    algo->intialize_data();

    // run algorithm
    algo->run();

    // restore the result 
    
    return 0;
}
