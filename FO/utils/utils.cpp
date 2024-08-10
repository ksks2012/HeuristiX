#include "utils.hpp"

FOBenchmark::FOBenchmark() {
    ;
}

FOBenchmark::FOBenchmark(int dimentions) {
    this->dimentions = dimentions;
}

void FOBenchmark::set_dimensions(int dimentions) {
    this->dimentions = dimentions;
}

/**
 * Sets the bounds for the given function number and dimension.
 *
 * @param func_num The function number.
 * @param dimension The dimension.
 */
void FOBenchmark::set_bounds(int func_num, int dimension) {
    // TODO: check if the bounds are effect by dimensions
    switch (func_num) {
        case 1:
            upper_bound = vector<double>(dimension, 100.0);
            lower_bound = vector<double>(dimension, -100.0);
            cout << "Bounds set for function number: " << func_num << " with size " << upper_bound.size() << " " << lower_bound.size() << endl;
            break;
        // TODO: more cases to be added...
        default:
            cerr << "\nError: Cannot find function number: " << func_num << endl;;
            break;
    }
}

/**
 * @brief This function is used to evaluate the CEC17 test functions.
 * 
 * @param x The input vector.
 * @param f The output vector.
 * @param nx The dimension of the input vector.
 * @param mx The number of vectors to be evaluated.
 * @param func_num The number of the test function to be evaluated.
 */
void FOBenchmark::cec17_test_func(const vector<vector<double>>& x, vector<double>& f, int nx, int mx, int func_num) {
    int cf_num = 10, i, j;

    if (ini_flag == 1) {
        if ((n_flag != nx) || (func_flag != func_num)) {
            ini_flag = 0;
        }
    }

    if (ini_flag == 0) {
        ifstream fpt;
        string file_name;

        // reinitialize the data
        y.clear();
        z.clear();
        y.resize(nx);
        z.resize(nx);

        if (!(nx == 2 || nx == 10 || nx == 20 || nx == 30 || nx == 50 || nx == 100)) {
            cerr << "\nError: Test functions are only defined for D=2,10,20,30,50,100.\n";
        }

        if (nx == 2 && ((func_num >= 17 && func_num <= 22) || (func_num >= 29 && func_num <= 30))) {
            cerr << "\nError: hf01,hf02,hf03,hf04,hf05,hf06,cf07&cf08 are NOT defined for D=2.\n";
        }

        // Load Matrix M
        file_name = "../dataset/CEC2017/input_data/M_" + to_string(func_num) + "_D" + to_string(nx) + ".txt";
        fpt.open(file_name);
        if (!fpt.is_open()) {
            cerr << "\nError: Cannot open input file for reading: " << file_name << endl;;
            return;
        }

        if (func_num < 20) {
            M.resize(nx * nx);
            for (i = 0; i < nx * nx; i++) {
                fpt >> M[i];
            }
        } else {
            M.resize(cf_num * nx * nx);
            for (i = 0; i < cf_num * nx * nx; i++) {
                fpt >> M[i];
            }
        }
        fpt.close();

        // Load shift_data
        file_name = "../dataset/CEC2017/input_data/shift_data_" + to_string(func_num) + ".txt";
        fpt.open(file_name);
        if (!fpt.is_open()) {
            cerr << "\nError: Cannot open input file for reading: " << file_name << endl;;
            return;
        }

        if (func_num < 20) {
            OShift.resize(nx);
            for (i = 0; i < nx; i++) {
                fpt >> OShift[i];
            }
        } else {
            OShift.resize(nx * cf_num);
            for (i = 0; i < cf_num - 1; i++) {
                for (j = 0; j < nx; j++) {
                    fpt >> OShift[i * nx + j];
                }
                fpt.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            for (j = 0; j < nx; j++) {
                fpt >> OShift[(cf_num - 1) * nx + j];
            }
        }
        fpt.close();

        // Load Shuffle_data
        if (func_num >= 11 && func_num <= 20) {
            file_name = "../dataset/CEC2017/input_data/shuffle_data_" + to_string(func_num) + "_D" + to_string(nx) + ".txt";
            fpt.open(file_name);
            if (!fpt.is_open()) {
                cerr << "\nError: Cannot open input file for reading: " << file_name << endl;;
                return;
            }
            SS.resize(nx);
            for (i = 0; i < nx; i++) {
                fpt >> SS[i];
            }
            fpt.close();
        } else if (func_num == 29 || func_num == 30) {
            file_name = "../dataset/CEC2017/input_data/shuffle_data_" + to_string(func_num) + "_D" + to_string(nx) + ".txt";
            fpt.open(file_name);
            if (!fpt.is_open()) {
                cerr << "\nError: Cannot open input file for reading: " << file_name << endl;;
                return;
            }
            SS.resize(nx * cf_num);
            for (i = 0; i < nx * cf_num; i++) {
                fpt >> SS[i];
            }
            fpt.close();
        }

        n_flag = nx;
        func_flag = func_num;
        ini_flag = 1;
    }

    for (i = 0; i < mx; i++) {
        switch (func_num) {
            case 1:
                this->bent_cigar_func(x[i], f[i], nx, OShift, M, 1, 1);
                f[i] += 100.0;
                break;
            case 2:
                cerr << "\nError: This function (F2) has been deleted\n";
                break;
            // TODO: Add other cases as needed...
            default:
                cerr << "\nError: There are only 30 test functions in this test suite!\n";
                f[i] = 0.0;
                break;
        }
    }
}

/**
 * @brief Shifts the elements of the input array by subtracting the corresponding elements of the shift array.
 * 
 * @param x The input array.
 * @param xshift The output array where the shifted elements will be stored.
 * @param nx The number of elements in the arrays.
 * @param Os The shift array containing the values to be subtracted from the input array.
 */
void FOBenchmark::shiftfunc(const vector<double>& x, vector<double>& xshift, int nx, vector<double>& Os) {
    int i;
    for (i = 0; i < nx; i++) {
        xshift[i] = x[i] - Os[i];
    }
}

/**
 * Rotates the given vector `x` using the rotation matrix `Mr`.
 * 
 * @param x The input vector to be rotated.
 * @param xrot The output vector after rotation.
 * @param nx The size of the vectors `x` and `xrot`.
 * @param Mr The rotation matrix.
 */
void FOBenchmark::rotatefunc(vector<double>& x, vector<double>& xrot, int nx, vector<double>& Mr) {
    int i, j;
    for (i = 0; i < nx; i++) {
        xrot[i] = 0;
        for (j = 0; j < nx; j++) {
            xrot[i] = xrot[i] + x[j] * Mr[i * nx + j];
        }
    }
}

/**
 * @brief Applies shift and rotation operations to the input vector `x` and stores the result in `sr_x`.
 * 
 * @param x The input vector.
 * @param sr_x The output vector to store the result of the shift and rotation operations.
 * @param nx The size of the input and output vectors.
 * @param Os The shift array containing the values to be subtracted from the input array.
 * @param Mr The rotation matrix used for rotation operation.
 * @param sh_rate The shrink rate to be applied to the input vector.
 * @param s_flag The flag indicating whether to perform shift operation (1) or not (0).
 * @param r_flag The flag indicating whether to perform rotation operation (1) or not (0).
 */
void FOBenchmark::sr_func(const vector<double>& x, vector<double>& sr_x, int nx, vector<double>& Os, vector<double>& Mr, double sh_rate, int s_flag, int r_flag) /* shift and rotate */
{
    int i;
    if (s_flag == 1) {
        if (r_flag == 1) {
            shiftfunc(x, y, nx, Os);
            for (i = 0; i < nx; i++) // shrink to the original search range
            {
                y[i] = y[i] * sh_rate;
            }
            rotatefunc(y, sr_x, nx, Mr);
        } else {
            shiftfunc(x, sr_x, nx, Os);
            for (i = 0; i < nx; i++) // shrink to the original search range
            {
                sr_x[i] = sr_x[i] * sh_rate;
            }
        }
    } else {
        if (r_flag == 1) {
            for (i = 0; i < nx; i++) // shrink to the original search range
            {
                y[i] = x[i] * sh_rate;
            }
            rotatefunc(y, sr_x, nx, Mr);
        } else
            for (i = 0; i < nx; i++) // shrink to the original search range
            {
                sr_x[i] = x[i] * sh_rate;
            }
    }
}

/**
 * Calculates the Bent Cigar function value for a given input vector.
 *
 * @param x The input vector.
 * @param f The output vector to store the function value.
 * @param nx The size of the input vector.
 * @param Os The shift vector.
 * @param Mr The rotation matrix.
 * @param s_flag The shift flag.
 * @param r_flag The rotation flag.
 */
void FOBenchmark::bent_cigar_func(const vector<double>& x, double& f, int nx, vector<double>& Os, vector<double>& Mr, int s_flag, int r_flag) /* Bent_Cigar */
{
    int i;
    sr_func(x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* shift and rotate */

    f = z[0] * z[0];
    for (i = 1; i < nx; i++) {
        f += pow(10.0, 6.0) * z[i] * z[i];
    }
}