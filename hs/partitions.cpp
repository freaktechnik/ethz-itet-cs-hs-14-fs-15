/**
 * CS Exercise 10.3
 * Title: partitions
 * Author: Martin Giger
 * Date: 26.06.2015
 * Vastly based off the provided template
 */

#include <iostream>

// PRE: [begin, end) is a valid nonempty range that describes
// a sequence of denominations d_1 > d_2 > ... > d_n > 0
// POST: return value is the number of ways to partition amount
// using denominations from d_1, ..., d_n
unsigned int partitions (unsigned int amount, const unsigned int* begin, const unsigned int* end)
{
    unsigned int i = 0;
    unsigned int c = 0;
    if(amount == 0) {
        ++i;
    }
    
    for(const unsigned int* a = begin; a != end; ++a) {
        if(*a <= amount) {
            c = amount - *a;
            if(c > 0) {
                i += partitions(c, a, end);
            }
            else if(c == 0) {
                ++i;
            }
        }
    }
    return i;
}

int main()
{
  // the 13 denominations of CHF
  unsigned int chf[] =
    {100000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};

  // input
  std::cout << "In how many ways can I own x CHF-centimes for x =? ";
  unsigned int x;
  std::cin >> x;

  // computation and output
  std::cout << partitions (x, chf, chf+13) << "\n";

  return 0;
}

