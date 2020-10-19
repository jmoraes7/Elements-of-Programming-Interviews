/*
* IsIntegerPalindrome.cpp
* -----------------
*
* Chapter 5 Question 9
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

int isPalindrome(int num) {
  if (num < 0) {
    return false;
  }  else if (num == 0) {
    return true;
  }

  const int kNumDigits = static_cast<int>(std::floor(std::log10(num))) + 1;
  int msd_mask = static_cast<int>(pow(10, kNumDigits - 1));
  for (int i = 0; i < (kNumDigits / 2); i++) {
    int first_digit = num / msd_mask;
    int last_digit = num % 10;

    if (first_digit != last_digit) {
      return false;
    }

    num %= msd_mask; //Remove most significant digit of x
    num /= 10; //Remove least significant digit of x
    msd_mask /= 100;
  }

  return true;
}

int main(int argc, char** argv) {  
  double x = 1239321;
  
  cout << isPalindrome(x) << " ";
  
  return 0;
}
 