/*
* Multiply.cpp
* -----------------
*
* Chapter 5 Question 5
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

unsigned Add(unsigned a, unsigned b) {
  unsigned sum = 0, carryin = 0, k = 1, temp_a = a, temp_b = b;

  while (temp_a || temp_b) {
    unsigned ak = a & k, bk = b & k;
    unsigned carryout = (ak & bk) | (ak & carryin) | (bk & carryin);
    sum |= (ak ^ bk ^ carryin);
    carryin = carryout << 1, k <<= 1, temp_a >>= 1, temp_b >>= 1;
  }

  return sum |= carryin;
}

unsigned Multiply(unsigned x, unsigned y) {
  unsigned sum = 0;
  while (x) {
    if (x & 1) {
      sum = Add(sum, y);
    }
    x >>= 1, y <<= 1;
  }
}

int main(int argc, char** argv) {  
  unsigned x = 17;
  unsigned y = 3;

  cout << Multiply(x, y);
  
  return 0;
}
