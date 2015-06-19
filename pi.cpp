/**
 * CS Exercise 4.4
 * Title: pi
 * Author: Martin Giger
 * Date: 19.06.2015
 */

#include <iostream>
#include <cmath>

using namespace std;

double getPi4Summand(const unsigned int n) {
    return (n % 2 == 1 ? -1.0 : 1.0) / (2 * n + 1); 
}

unsigned long fac(const unsigned int n) {
    unsigned long ret = 1;
    for(unsigned int i = 1; i <= n; ++i) {
        ret *= i;
    }
    return ret;
}

unsigned long unevenFac(const unsigned int n) {
    unsigned long ret = 1;
    for(unsigned int i = 1; i <= n; ++i) {
        ret *= (2 * i) + 1;
    }
    return ret;
}

// This method is extremely prone to overflow errors, even with unsigned longs
// for the fctorial calculation
double getPi2Summand(const unsigned int n) {
    cout << fac(n) << " " << unevenFac(n) << endl;
    return (double)fac(n) / (double)unevenFac(n);
}

double getPi(const unsigned int n, const unsigned int m) {
    double pi = 0;
    for(unsigned int i = 0; i <= n; ++i) {
        if(m == 4) {
            pi += getPi4Summand(i);
        }
        else {
            pi += getPi2Summand(i);
        }
    }
    return pi * m;
}

int main(void) {
    unsigned int accuracy;
    cout << "Accuracy of the calculation of PI:";
    cin >> accuracy;
    
    unsigned int method;
    cout << "Choose the method of calculation (2/4):";
    cin >> method;
    
    if(method != 2 && method != 4) {
        cout << "No valid method" << endl;
        return 1;
    }
    
    cout << "PI: " << getPi(accuracy, method) << endl;
    
    //cout << "The builtin PI constant for comparison: " << PI << endl;
    
    return 0;
}
