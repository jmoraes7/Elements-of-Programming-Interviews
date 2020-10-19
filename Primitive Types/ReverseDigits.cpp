/*
* ReverseDigits.cpp
* -----------------
*
* Chapter 5 Question 8
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

int reverseDigits(int num) {
  bool is_negative = num < 0; 
  long result = 0, num_remaining = abs(num);

  while (num_remaining) {
    result = result * 10 + num_remaining % 10;
    num_remaining /= 10;
  }

  return is_negative ? -result : result;
}

int main(int argc, char** argv) {  
  double x = -12245;
  
  cout << reverseDigits(x) << " ";
  
  return 0;
}
 