/**
 * CS Exercise 7.3
 * Title: array
 * Author: Martin Giger
 * Date: 19.06.2015
 */

#include <iostream>
#include <climits>
#include <array>
#include <string>

using namespace std;

const unsigned int SIZE = 10;

// i)
int max(const array<int, SIZE> array) {
    int max = INT_MIN;
    for(unsigned int i = 0; i < SIZE; ++i) {
        if(array[i] > max) {
            max = array[i];
        }
    }

    return max;
}

int min(const array<int, SIZE> array) {
    int min = INT_MAX;
    for(unsigned int i = 0; i < SIZE; ++i) {
        if(array[i] < min) {
            min = array[i];
        }
    }

    return min;
}

// ii)
unsigned int getMaxSequenceLength(const array<int, SIZE> array) {
    unsigned int length = 1, currLength = 1;

    for(unsigned int i = 1; i < SIZE; ++i) {
        if(array[i-1] < array[i]) {
            if(++currLength > length) {
                ++length;
            }
        }
        else {
            currLength = 0;
        }
    }

    return length;
}

// iii) [bubble sort]

array<int, SIZE> bubbleSort(array<int, SIZE> array) {
    unsigned int swaps;
    int cache;
    
    do {
        swaps = 0;
        for(unsigned int i = 1; i < SIZE; ++i) {
            if(array[i-1] > array[i]) {
                cache = array[i-1];
                array[i-1] = array[i];
                array[i] = cache;
                ++swaps;
            }
        }
    } while(swaps > 0);

    return array;
}

void prettyPrintArray(const array<int, SIZE> array) {
    cout << "[";
    for(unsigned int i = 0; i < SIZE; ++i) {
        if(i > 0) {
            cout << ",";
        }
        cout << array[i];
    }
    cout << "]";
}

int main(void) {
    array<int, SIZE> array;
    cout << "Enter 10 integers:" << endl;
    for(unsigned int i = 0; i < SIZE; ++i) {
        cin >> array[i];
    }

    // i)
    cout << "Smallest integer in the input: " << min(array) << endl;
    cout << "Biggest integer in the input: " << max(array) << endl;

    // ii)
    cout << "Longest sequence: " << getMaxSequenceLength(array) << endl;

    // iii)
    cout << "Sorted array: ";
    prettyPrintArray(bubbleSort(array));
    cout << endl;

    return 0;
}
