/*
* ComputeIntegerSquareRoot.cpp
* -----------------
*
* Chapter 12 Question 5
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

int ComputeSquareRoot(int k) {
  int left = 0, right = k;

  while (left <= right) {
    long mid = left + ((right - left) / 2);
    long mid_squared = mid * mid;
    
    cout << "LEFT: " << left << " RIGHT: " << right << " MID: " << mid << endl;

    if (mid_squared > k) {
      right = mid - 1;
    } else {
      left = mid + 1;
    } 
  }

  return left - 1;
}

int main(int argc, char** argv) {
  int k = 15;
  int square_root = ComputeSquareRoot(k);

  cout << "Integer Square root of: " << k << " = " << square_root << endl;

  return 0;
}
