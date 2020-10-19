/*
* GenerateUniformRandomNumbers.cpp
* -----------------
*
* Chapter 5 Question 10
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

int ZeroOneRandom() {
  default_random_engine gen((random_device())());
  uniform_int_distribution<int> dis(0,1);
  return dis(gen);
}

int UniformRandom(int lower_bound, int upper_bound) {
  int number_of_outcomes = upper_bound - lower_bound + 1, result;
  do {
    result = 0;
    for (int i = 0; (1 << i) < number_of_outcomes; i++) {
      result = result << 1 | ZeroOneRandom();
    }

  } while (result >= number_of_outcomes);
  return result + lower_bound;
}

int main(int argc, char** argv) {  
  int a = 1;
  int b = 6;

  int x = UniformRandom(a, b);
  cout << "a = " << a << " b = " << b << endl;
  cout << "random result = " << x << endl;
  assert(x >= a && x <= b);
  
  return 0;
}
 