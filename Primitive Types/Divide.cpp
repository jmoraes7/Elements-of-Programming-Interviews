/*
* Divide.cpp
* -----------------
*
* Chapter 5 Question 6
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

unsigned Divide(unsigned x, unsigned y) {
  unsigned result = 0;
  int power = 32;
  unsigned long long y_power = static_cast<unsigned long long>(y) << power; 

  while (x >= y) {
    while (y_power > x) {
      y_power >>= 1;
      --power;
    }

    result += 1U << power;
    x -= y_power;
  }
  return result;
}

int main(int argc, char** argv) {  
  unsigned x = 18;
  unsigned y = 3;

  cout << Divide(x, y);
  
  return 0;
}
 