#include "header.hpp"
#include "pso.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    // check the number of arguments
    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " -algo <algorithm> -dataset <path_to_dataset>" << endl;
        return 1;
    }

    string algorithm;
    string function_number;
    string dimentions;

    // parse the arguments
    for (int i = 1; i < argc; i += 2) {
        string flag = argv[i];
        if (flag == "-algo") {
            algorithm = argv[i + 1];
        } else if (flag == "-func") {
            function_number = argv[i + 1];
        } else if (flag == "-dim") {
            dimentions = argv[i + 1];
        } else {
            cerr << "Unknown flag: " << flag << endl;
            return 1;
        }
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
        algo = new PSO();
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
