/**
 * CS Exercise 2.3
 * Title: equivres
 * Author: Martin Giger 
 * Date: 19.06.2015
 */

#include <iostream>

using namespace std;

int serialResistance(const int r1, const int r2) {
    return r1 + r2;
}

int parallelResistance(const int r1, const int r2) {
    return (r1 + r2)/(r1*r2);
}

int main(void) {
    int r1, r2, r3, r4;
    cout << "Calculate the resistance of the following schema:" << endl;
    cout << "       ----       ----" << endl;
    cout << "     --|R1|-------|R2|--" << endl;
    cout << "     | ----       ---- |" << endl;
    cout << "-----|                 |-----" << endl;
    cout << "     | ----       ---- |" << endl;
    cout << "     --|R3|-------|R4|--" << endl;
    cout << "       ----       ----" << endl << endl;
    cout << "Value of R1:";
    cin >> r1;
    cout << "Value of R2:";
    cin >> r2;
    cout << "Value of R3:";
    cin >> r3;
    cout << "Value of R4:";
    cin >> r4;
    cout << endl << "The equivalent resistance is "<< parallelResistance(serialResistance(r1, r2), serialResistance(r3, r4)) << endl;
    
    return 0;
}

