/*
* MaxContiguousSubarray2D.cpp
* -----------------
*
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_real_distribution;
using std::string;
using std::vector;

std::pair<int, int> MaxContiguousSubarrayQuadratic(const vector<int>& A) {
  int max_sum = 0;
  std::pair<int, int> max_subarray_idx;

  for (int i = 0; i < A.size(); i++) {
    int sum = 0;
    for (int j = i; j < A.size(); j++) {
      sum += A[j];

      if (sum > max_sum) {
        max_sum = sum;
        max_subarray_idx = {i, j};
      }
    }
  }
  return max_subarray_idx;
}

std::pair<int, int> MaxContiguousSubarray(const vector<int>& A) {
  std::pair<int, int> max_subarray_idx;
  
  int max_sum = std::numeric_limits<int>::min();
  int sum = 0; 
  int start = 0, end = 0;
  for (int i = 0; i < A.size(); i++) {
    sum = sum + A[i];

    if (sum < A[i]) {
      sum = A[i];
      start = i;
    }

    if (sum > max_sum) {
      max_sum = sum;
      end = i;
    }
  }

  return {start, end};
}

int main(int argc, char** argv) {   
  
  vector<int> arr{-1, 904, 40, 523, 12, -335, -385, -124, 481, -31};

  auto idx = MaxContiguousSubarray(arr);

  cout << idx.first << " " << idx.second << endl;

  return 0;
}

