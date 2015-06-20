/**
 * CS Exercise 9.3
 * Title: string search
 * Author: Martin Giger
 * Date: 20.06.2015
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef string::iterator Iterator;

// returns true if string at first1, last1 is lexicographically
// smaller than string at first2, last2
// From exercise 9.2
bool lexicographic_compare(Iterator first1, Iterator last1, Iterator first2, Iterator last2) {
    while(first1 != last1 && first2 != last2 && *first1 == *first2) {
        ++first1;
        ++first2;
    }
    return *first1 < *first2 || (*first1 == *first2 && last1 - first1 < last2 - first2);
}

string findLastString(const vector<string> &strings) {
    string max = strings.front(), curr;
    for(vector<string>::const_iterator i = strings.begin(); i != strings.end(); ++i) {
        curr = (string) *i;
        if(lexicographic_compare(max.begin(), max.end(), curr.begin(), curr.end())) {
            max = curr;
        }
    }
    return max;
}

int main(void) {
    vector<string> strings;
    
    int n;
    cout << "Number of strings: ";
    cin >> n;
    
    string input;
    for(int i = 0; i < n; ++i) {
        cin >> input;
        strings.push_back(input);
    }
    
    cout << findLastString(strings) << endl;
    
    return 0;
}
