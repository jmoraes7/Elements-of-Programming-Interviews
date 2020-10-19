/*
* GCD.cpp
* -----------------
*
* Chapter 22 Question 2
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::array;
using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::random_device;
using std::stoul;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

long long GCDInefficient(long long x, long long y) {
  if (x < y) std::swap(x, y);
  return y == 0 ? x : GCDInefficient(y, x % y);
}

long long GCD (long long x, long long y) {
  if (x == 0) {
    return y;
  } else if (y == 0) {
    return x;
  } else if (!(x & 1) && !(y & 1)) { //x and y are even
    return GCD(x >> 1, y >> 1) << 1;
  } else if ((x & 1) && !(y & 1)) { //x is even, y is odd
    return GCD(x, y >> 1);
  } else if (!(x & 1) && (y & 1)) { //x is odd, y is even
    return GCD(x >> 1, y);
  } else if (x > y) { //x and y are odd; x > y
    return GCD(x-y, y);
  }
  return GCD(x, y - x); //x and y are odd; x <= y
}

int main(int argc, char** argv) {   
  
  int x = 24;
  int y = 300;
  int z = 25;

  cout << GCDInefficient(y, z) << " " << GCDInefficient(z, y) << endl;
  cout << (1 >> 1) << endl;
  
  return 0;
}


