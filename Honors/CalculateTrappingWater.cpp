/*
* CalculateTrappingWater.cpp
* -----------------
*
* Chapter 22 Question 42
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <iterator>     // std::distance
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::greater;
using std::hash;
using std::istringstream;
using std::length_error;
using std::make_unique;
using std::unique_ptr;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::stoi;
using std::unordered_map;
using std::unordered_set;
using std::vector;

int CalculateTrappingWater(vector<int> &A) {
  int sum = 0;

  vector<int> right_max(A.size(), 0);
  right_max.front() = A.front();
  for (int i = 1; i < A.size(); i++) {
    right_max[i] = std::max(right_max[i-1], A[i]);
  }

  vector<int> left_max(A.size(), 0);
  left_max.back() = A.back();
  for (int i = A.size() - 2; i >= 0; i--) {
    left_max[i] = std::max(left_max[i+1], A[i]);
  }

  for (int i = 0; i < A.size(); i++) {
    sum += std::min(left_max[i], right_max[i]) - A[i];
  }
  
  return sum;
}

int CalculateTrappingWaterConstantSpace(vector<int> &A) {
  if (A.empty()) {
    return 0;
  }


  int max_h = std::numeric_limits<int>::min(), max_idx = -1;
  for (int i = 0; i < A.size(); i++) {
    if (A[i] > max_h) {
      max_h = A[i];
      max_idx = i;
    }
  }

  int sum = 0, left = A.front();
  for (int i = 1; i < max_idx; ++i) {
    if (A[i] >= left) {
      left = A[i];
    } else {
      sum += left - A[i];
    }
  }

  int right = A.back();
  for (int i = A.size() - 2; i > max_idx; i--) {
    if (A[i] >= right) {
      right = A[i];
    } else {
      sum += right - A[i];
    }
  }

  return sum;
}

int main(int argc, char** argv) {   

  vector<int> A{1, 2, 1, 3, 4, 4, 5, 1, 2, 0, 3};

  cout << CalculateTrappingWater(A) << " "
     << CalculateTrappingWaterConstantSpace(A) << endl;

  return 0;
}


