/*
* MajorityElement.cpp
* -----------------
*
* Chapter 18 Question 6
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

int getMajorityElement(vector<int> A) {
  int candidate = A[0], count = 1;

  for (int i = 1; i < A.size(); i++) {
    if (count == 0) {
      candidate = A[i];
      count = 1;
    } else if (candidate = A[i]) {
      count++;
    } else {
      count--;
    }
  }

  return candidate;
}

int main(int argc, char** argv) {   
  
  vector<int> A{5, 5, 2, 1, 5};
  
  cout << getMajorityElement(A) << endl;

  return 0;
}


