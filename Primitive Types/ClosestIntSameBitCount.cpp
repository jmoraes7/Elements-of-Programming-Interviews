/*
* ClosestIntSameBitCount.cpp
* -----------------
*
* Chapter 5 Question 4
*/

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::invalid_argument;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

long swapBits(long x, int i, int j) {
  unsigned long bitMask = (1UL << i) | (1UL << j);
  return x^= bitMask;
}
/*
* Swap the first 2 consecutive bits that differ
*/
unsigned long ClosestIntSameBitCount(unsigned long x) {
  const static int kNumUnsignedBits = 64;
  for (int i = 0; i < kNumUnsignedBits - 1; i++) {
    if (((x >> i) & 1) != ((x >> (i+1)) &1)) {
       return swapBits(x, i, i+1); 
    }
  }

  throw invalid_argument("all bits are 0 or 1");
}

int main(int argc, char** argv) {  
  unsigned long x = 7;

  cout << ClosestIntSameBitCount(x);
  
  return 0;
}
