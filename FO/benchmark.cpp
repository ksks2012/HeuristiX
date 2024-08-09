#include "algo.hpp"
#include "utils.hpp"

int main() {
    int i, j, k, n, m, func_num;
    vector<double> f, x;

    m = 2;
    n = 10;
    x.resize(m * n);
    f.resize(m);

    for (i = 0; i < 1; i++) {
        func_num = i + 1;
        string fileName = "../dataset/CEC2017/input_data/shift_data_" + to_string(func_num) + ".txt";
        ifstream fpt(fileName);
        
        if (!fpt.is_open()) {
            cerr << "\nError: Cannot open input file for reading: " << fileName << "\n";
            continue;
        }

        for (k = 0; k < n; k++) {
            fpt >> x[k];
        }

        fpt.close();

        for (j = 0; j < n; j++) {
            x[1 * n + j] = 0.0;
        }

        FOBenchmark *benchmark = new FOBenchmark();

        for (k = 0; k < 1; k++) {
            benchmark->cec17_test_func(x, f, n, m, func_num);
            for (j = 0; j < m; j++) {
                cout << " f" << func_num << "(x[" << j + 1 << "]) = " << f[j] << ",";
            }
            cout << "\n";
        }
    }
    return 0;
}
