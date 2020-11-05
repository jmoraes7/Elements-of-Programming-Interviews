/*
* MaxSubarraySumCircular.cpp
* -----------------
*
* Chapter 22 Question 38
*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;

using std::default_random_engine;
using std::endl;
using std::get;
using std::hash;
using std::numeric_limits;
using std::ostream;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

int MaxSubarraySum(const vector<int>& A) {
  int max_sum = A[0], curr = A[0];
  for (int i = 1; i < A.size(); i++) {
    curr = std::max(curr + A[i], A[i]);
    max_sum = std::max(max_sum, curr);
  }
  
  return max_sum;
}

int MaxSubarraySumInCircular(const vector<int>& A) {
  int backward_subarray_idx = A.size() - 1;
  int max_sum_backward = A[backward_subarray_idx];
  int curr = max_sum_backward;
  
  for (int i = backward_subarray_idx - 1; i > 0; i--) {
    if (curr + A[i] < curr) {
      break;
    }

    curr += A[i];

    if (curr > max_sum_backward) {
      max_sum_backward = curr;
      backward_subarray_idx = i;
    }

  }
  
  // cout << "MAX BACKWARD: " << max_sum_backward << " IDX " << backward_subarray_idx << endl;

  int max_sum_forward = A[0];
  curr = max_sum_forward;
  for (int i = 1; i < backward_subarray_idx; i++) {
    curr = std::max(curr, curr + A[i]);
    max_sum_forward = std::max(max_sum_forward, curr);
  }

  // cout << "MAX FORWARD: " << max_sum_forward << endl;

  int max_sum_not_circular = MaxSubarraySum(A);

  return std::max(max_sum_forward + max_sum_backward,
                    max_sum_not_circular);
}

/*
* Book Solutions
*/
int FindCircularMaxSubarray(const vector<int>& A) {
  vector<int> max_begin;
  int sum = A.front();
  max_begin.emplace_back(sum);
  for (int i = 1; i < A.size(); ++i) {
    sum += A[i];
    max_begin.emplace_back(std::max(max_begin.back(), sum));
  }

  vector<int> max_end(A.size());
  max_end.back() = 0;
  sum = 0;
  for (int i = A.size() - 2; i >= 0; i--) {
    sum += A[i+1];
    max_end[i] = std::max(max_end[i+1], sum);
  }

  // cout << "FORWARD:" << endl;
  // for (int x : max_begin) {
  //   cout << x << " ";
  // }
  // cout << endl;

  // cout << "BACKWARD: " << endl;
  // for (int x : max_end) {
  //   cout << x << " ";
  // }
  // cout << endl;

  int circular_max = 0;
  for (int i = 0; i < A.size(); i++) {
    circular_max = std::max(circular_max, max_begin[i] + max_end[i]);
  }

  return std::max(MaxSubarraySum(A), circular_max);
}

/*
* Compute minimum subarray
*/
int FindOptimumSubarrayUsingComp(const vector<int>& A,
              const int& (*comp)(const int&, const int&)) {

}

int MaxSubarraySumInCircularClean(const vector<int>& A) {
  int max_sum_reg = MaxSubarraySum(A);

  int min_sum_reg = A[0], curr = A[0];
  for (int i = 1; i < A.size(); i++) {
    cout << "CURR: " << curr << endl;
    curr = std::min(A[i], curr + A[i]);
    min_sum_reg = std::min(min_sum_reg, curr);
  } 

  int circular_sum = accumulate(A.begin(), A.end(), 0) - min_sum_reg;
  cout << "MIN: " << min_sum_reg << endl;
  cout << "TOTAL: " << accumulate(A.begin(), A.end(), 0) << endl;
  return std::max(max_sum_reg, circular_sum);
}

int main(int argc, char** argv) {   
  
  vector<int> A = {904, 40, 523, 12, -355, -385, -124, 481, -31};
  vector<int> B = {10, -4, 5, -4, 10};
  
  cout << MaxSubarraySumInCircularClean(B) << endl;

  return 0;
}


