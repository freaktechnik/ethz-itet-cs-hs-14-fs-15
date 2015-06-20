/**
 * CS Exercise 9.1
 * Title: insertion sort
 * Author: Martin Giger
 * Date: 20.06.2015
 */

#include <iostream>

using namespace std;

void input(int* const begin, const int* const end) {
    cout << "Input " << end - begin << " array elements:" << endl;
    int* curr = begin;
    while(curr != end) {
        cin >> *curr;
        ++curr;
    }
}

void output(int* const begin, const int* const end) {
    cout << "[ " << *begin;
    int* curr = begin + 1;
    while(curr != end) {
        cout << ", " << *curr;
        ++curr;
    }
    cout << " ]" << endl;
}

void swap(int* const element1, int* const element2) {
    if(element1 != element2) {
        int copy = *element2;
        *element2 = *element1;
        *element1 = copy;
    }
}

int* minimum(int* const begin, const int* const end) {
    int* curr = begin;
    int* min = begin;
    while(curr != end) {
        if(*curr < *min) {
            min = curr;
        }
        ++curr;
    }
    return min;
}

bool swapFirstWithMinimum(int* const begin, const int* const end) {
    int* min = minimum(begin, end);
    if(*begin != *min) {
        swap(begin, min);
        return true;
    }
    else {
        return false;
    }
}

bool sortPass(int* const begin, int* const end) {
    int* curr = end - 2;
    bool swapped = false;
    while(curr >= begin) {
        if(swapFirstWithMinimum(curr, end)) {
            swapped = true;
        }
        --curr;
    }
    
    return swapped;
}

void sort(int* const begin, int* const end) {
    int* curr = begin;
    bool swapped = true;
    while(curr != end && swapped) {
        swapped = sortPass(curr, end);
        ++curr;
    }        
}

int main(void) {
    const int N = 10;
    int array[N];
    
    int* begin = &array[0];
    int* end = &array[N];
    
    input(begin, end);
    
    sort(begin, end);
    
    output(begin, end);
    
    return 0;
}
