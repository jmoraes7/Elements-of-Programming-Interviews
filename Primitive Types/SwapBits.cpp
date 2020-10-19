/*
* SwapBits.cpp
* -----------------
*
* Chapter 5 Question 2
*/

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>

using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;

void int_to_bin(int num)
{
  char str[9] = {0};
  int i;
  for (i=7; i>=0; i--)
  {
    str[i] = (num&1) ? '1' : '0';
    num >>= 1;
  }
  cout << str << endl;
}

long swapBits(long x, int i, int j) {
  int bit_at_i = (x >> i) & 1;
  int bit_at_j = (x >> j) & 1;

  if (bit_at_i != bit_at_j) {
    // result ^= (1 << i);
    // result ^= (1 << j);
    unsigned long bitmask = (1 << i) | (1 << j);
    x ^= bitmask; 
  }
  
  cout << "Bit at i: " << bit_at_i << "; Bit at j: " << bit_at_j << endl;

  return x;
}

int main(int argc, char** argv) {  

  unsigned long x = 10;

  x = swapBits(x, 1, 2);

  cout << x;

  return 0;
}
