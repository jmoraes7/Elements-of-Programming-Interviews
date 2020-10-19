/*
* ComputeExponetial.cpp
* -----------------
*
* Chapter 5 Question 7
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

double Pow(double x, int y) {
  if (y == 0) { return 1; }

  double temp = Pow(x, y/2);

  if ((y % 2) == 0) {
    return temp * temp;
  } else {
    return temp * temp * x;
  }
}

double Power(double x, int y) {
  double result = 1.0;
  long long power = y;
  if (power < 0) {
    power = -power, x = 1.0 / x;
  }

  while (power) {
    cout << power << endl;
    if (power & 1) {
      result *= x;
    }

    x *= x, power >>=1;
  }
  return result;
}

int main(int argc, char** argv) {  
  double x = 2;
  int y = 7;

  
  cout << Pow(x, y) << " ";
  
  return 0;
}
 