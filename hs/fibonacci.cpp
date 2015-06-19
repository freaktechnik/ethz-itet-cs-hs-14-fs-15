/**
 * CS Exercise 3.4
 * Title: fibonacci
 * Author: Martin Giger
 * Date: 19.06.2015
 */

#include <iostream>
#include <math.h>
#include <limits.h>

using namespace std;

bool isPrime(const unsigned int n) {
    bool isNotPrime = false;

    unsigned int s = sqrt(n);

    for(unsigned int i = 2; i <= s; ++i) {
        if(n % i == 0) {
            isNotPrime = true;
            break;
        }
    }

    return !isNotPrime;
}

int main(void) {
    // Allow the limit to be so big that the fibonacci numbers can overflow
    unsigned long limit;
    cout << "Calculate fibonacci primes between 0 and ";
    cin >> limit;

    cout << "0";

    for(unsigned int a = 0, b = 1, c = 0; b < limit; b = a + b) {
        a = c;

        // Overflow detection
        if(b < a) {
            cout << endl << "Error: Fibonacci Number too big to calculate";
            break;
        }
        else if(isPrime(b)) {
            cout << "," << b;
        }

        c = b;
    }

    cout << endl;

    return 0;
}
