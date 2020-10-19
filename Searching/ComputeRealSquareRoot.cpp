/*
* ComputeRealSquareRoot.cpp
* -----------------
*
* Chapter 12 Question 6
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
using std::numeric_limits;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

double ComputeRealSquareRoot(double x) {
  double left, right;
  if (x < 1.0)  {
    left = x, right = 1.0;
  } else {
    left = 1.0, right = x;
  }

  double eps = 1e-8;//numeric_limits<double>::epsilon();
  int count = 0;

  while (right - left > eps) {
    double mid = left + (right - left) / 2;
    double mid_squared = mid * mid;
    cout << "LEFT: " << left << " RIGHT: " << right << " MID: " << mid << " DIFF: " << abs(mid_squared - x) << " EPS: " << eps << endl; 
    cout << (abs(mid_squared - x) < eps) << endl << endl;
    
    
    if (abs(mid_squared - x) < eps ) {
      return mid;
    } else if (mid_squared < x) {
      left = mid;
    } else {
      right = mid;
    }
    count++;
    if (count == 5000) { return left; }
  }
  

  return left;
}

int main(int argc, char** argv) {
  double k = .25;
  double square_root = ComputeRealSquareRoot(k);

  // cout << -numeric_limits<double>::epsilon() << endl;

  cout << "Real Square root of: " << k << " = " << square_root << endl;

  return 0;
}
