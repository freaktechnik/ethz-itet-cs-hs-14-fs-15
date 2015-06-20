/**
 * CS Exercise 9.2
 * Title: lexicographic comparison
 * Author: Martin Giger
 * Date: 20.06.2015
 */

#include <iostream>
#include <string>

using namespace std;

typedef string::iterator Iterator;

// returns true if string at first1, last1 is lexicographically
// smaller than string at first2, last2
bool lexicographic_compare(Iterator first1, Iterator last1, Iterator first2, Iterator last2) {
    while(first1 != last1 && first2 != last2 && *first1 == *first2) {
        ++first1;
        ++first2;
    }
    return *first1 < *first2 || (*first1 == *first2 && last1 - first1 < last2 - first2);
}

// main function from the exercise
int main() {
    // string input
    string name1;
    string name2;
    cin >> name1;
    cin >> name2;
    // output result for standard library strings
    if (lexicographic_compare (name1.begin(), name1.end(), name2.begin(), name2.end()))
    cout << name1 << "<" << name2 << "\n";
    else
    cout << name1 << ">=" << name2 << "\n";
    return 0;
}
