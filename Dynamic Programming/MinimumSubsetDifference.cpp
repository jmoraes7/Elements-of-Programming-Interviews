/*
* MinimumSubsetDifference.cpp
* -----------------
*
* Chapter 17 Question 7
*/

#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::hash;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::tuple;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

int MinimizeDifference(vector<int>& A) {
  int sum = accumulate(A.begin(), A.end(), 0);

  unordered_set<int> possible_sums;
  possible_sums.insert(0);

  for (const int& item : A) {
    
    for (int i = sum; i >= item; i--) {
      if (possible_sums.count(i - item)) {
        possible_sums.emplace(i);
      }
    }
  }

  for (int i = sum / 2; i > 0; i--) {
    if (possible_sums.count(i)) {
      return (sum - i) - i;
    }
  }

  return sum; //all elements in A go into one set 
}

int main(int argc, char** argv) {   
  
 vector<int> A {65,  35,  245, 195, 65,  150, 275, 155,
                   120, 320, 75,  40,  200, 100, 220, 99};

  cout << MinimizeDifference(A) << endl;


  return 0;
}

