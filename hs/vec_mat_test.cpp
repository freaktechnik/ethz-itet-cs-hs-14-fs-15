/**
 * CS Exercise 8.1
 * Title: vec_mat_test
 * Author: Martin Giger
 * Date: 19.06.2015
 */

#include <iostream>
#include <string>
#include <array>

using namespace std;

const unsigned int DIM = 3;

const array<string, DIM> DIM_NAMES = {
    "x",
    "y",
    "z"
};

void input_vector(float res[DIM]) {
    cout << "Entering a " << DIM << "D vector." << endl;
    for(unsigned int i = 0; i < DIM; ++i) {
        cout << DIM_NAMES[i] << ": ";
        cin >> res[i];
    }
}

float scalar_product(const float v1[DIM], const float v2[DIM]) {
    float ret = 0;
    for(unsigned int i = 0; i < DIM; ++i) {
        ret += v1[i] * v2[i];
    }
    return ret;
}

void input_matrix(float matrix[DIM][DIM]) {
    cout << "Entering a " << DIM << "x" << DIM << " matrice. Enter it in normal formatting, separating horizontally with spaces." << endl;
    for(unsigned int i = 0; i < DIM; ++i) {
        for(unsigned int j = 0; j < DIM; ++j) {
            cin >> matrix[i][j];
        }
    }
}

void output_matrix(const float matrix[DIM][DIM]) {
    for(unsigned int i = 0; i < DIM; ++i) {
        for(unsigned int j = 0; j < DIM; ++j) {
            cout << " " << matrix[i][j];
        }
        cout << endl;
    }
}

void matrix_multiplication(const float a[DIM][DIM], const float b[DIM][DIM], float res[DIM][DIM]) {
    for(unsigned int i = 0; i < DIM; ++i) {
        for(unsigned int j = 0; j < DIM; ++j) {
            for(unsigned int k = 0; k < DIM; ++k) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(void) {
    // b) i)
    float v1[DIM], v2[DIM];
    input_vector(v1);
    input_vector(v2);
    
    cout << scalar_product(v1, v2) << endl;
    
    // b) ii)
    float a[DIM][DIM], b[DIM][DIM], res[DIM][DIM];
    input_matrix(a);
    input_matrix(b);
    
    matrix_multiplication(a, b, res);
    
    output_matrix(res);
    
    return 0;
}
