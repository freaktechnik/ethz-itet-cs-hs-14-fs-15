/**
 * CS Exercise 5.2
 * Title: inline
 * Author: Martin Giger
 * Date: 19.06.2015
 */

#include <iostream>

using namespace std;

const double DELTA = 0.01;

// y = 2.1 · x + 0.5
double line(double x) {
    return 2.1 * x + 0.5;
}

bool isInLine(double x, double y) {
    return line(x) - y < DELTA;
}

int main(void) {
    cout << "Check whether a point is in the line 2.1 · x + 0.5" << endl;

    double x, y;
    cout << "X-coordinate of the point: ";
    cin >> x;
    cout << "Y-coordinate of the point: ";
    cin >> y;
    
    if(isInLine(x, y)) {
        cout << "The point (" << x << "," << y << ") is in the line" << endl;
    }
    else {
        cout << "The point (" << x << "," << y << ") is not in the line" << endl;
    }
    
    return 0;
}
