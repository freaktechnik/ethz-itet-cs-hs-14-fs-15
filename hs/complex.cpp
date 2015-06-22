/**
 * CS Exercise 10.1
 * Title: complex
 * Author: Martin Giger
 * Date: 22.06.2015
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

const double DELTA = 0.0000000001;
const string SEPARATOR = "+i";

// not needed with C++11
double stod(const string& s) {
    istringstream i(s);
    double x;
    i >> x;
    return x;
}

struct complex {
    complex(double x = 0, double y = 0): x(x), y(y) {};
    double x;
    double y;
    
    complex operator+(const complex& other) const {
        complex r;
        r.x = this->x + other.x;
        r.y = this->y + other.y;
        return r;
    }
    
    complex operator-(const complex& other) const {
        complex r;
        r.x = this->x - other.x;
        r.y = this->y - other.y;
        return r;
    }
    
    complex operator*(const complex& other) const {
        complex r;
        r.x = this->x * other.x - this->y * other.y;
        r.y = this->x * other.y + this->y * other.x;
        return r;
    }
    
    complex operator*(const double lambda) const {
        complex r;
        r.x = this->x * lambda;
        r.y = this->y * lambda;
        return r;
    }
    
    complex operator/(const complex& other) const {
        double f = pow(other.x, 2) + pow(other.y, 2);
        complex r;
        r.x = (this->x * other.x + this->y * other.y) / f;
        r.y = (this->y * other.x - this->x * other.y) / f;
        return r;
    }
    
    bool operator==(const complex& other) const {
        return this->x - other.x < DELTA && this->y - other.y < DELTA;
    }
    
    bool operator!=(const complex& other) const {
        return this->x - other.x >= DELTA && this->y - other.y >= DELTA;
    }
    
    void print(std::ostream& os) const {
        os << this->x << SEPARATOR << this->y;
    }
    
    double abs() const {
        return sqrt(pow(this->x, 2) + pow(this->y, 2));
    }
};

istream& operator>>(istream& is, complex& c) {
    stringbuf sb;
    is.get(sb);
    
    string buf = sb.str();
    
    int split = buf.find(SEPARATOR);
    
    c.x = stod(buf.substr(0, split));
    
    c.y = stod(buf.substr(split + SEPARATOR.length(), string::npos));

    return is;
}

ostream& operator<<(ostream& os, const complex& c) {
    c.print(os);
    return os;
}
