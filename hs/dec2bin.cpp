/**
 * CS Exercise 3.3
 * Title: dec2bin
 * Author: Martin Giger
 * Date: 19.06.2015
 */

#include <iostream>

using namespace std;

void binary(const unsigned int n) {
    //TODO this outputs the binary the wrong way around
    for(unsigned int b = n; b > 0; b = b / 2) {
        cout << b % 2;
    }
}

int main(void) {
    int n;
    cout << "Enter a Number for conversion to binary:";
    cin >> n;
    if(n < 0) {
        n = -n;
    }

    binary(n);
    cout << endl;
    return 0;
}
