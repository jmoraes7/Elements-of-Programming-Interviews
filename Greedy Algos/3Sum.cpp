/*
* 3Sum.cpp
* -----------------
*
* Chapter 18 Question 5
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

vector<int> getTwoSum(vector<int> A, int t, int ignore_idx) {
  //A.erase(A.begin() + ignore_idx);
  int size = A.size();
  int i = ignore_idx == 0 ? 1 : 0;
  int j = (ignore_idx == size - 1) ? size - 2 : size - 1;
  
  while (i < j) {
    int sum = A[i] + A[j];
    if (sum == t) {
      return {A[i], A[j]};
    } else if (sum < t) {
      i = (i + 1 == ignore_idx) ? i + 2 : i + 1;
    } else {
      j = (j - 1 == ignore_idx) ? j - 2 : j - 1;
    }
  }

  return {};
}

vector<int> GetThreeSum(vector<int> A, int t) {
  sort(A.begin(), A.end());

  for (int i = 0; i < A.size(); i++) {
    vector<int> three_sum = getTwoSum(A, t - A[i], i);
    if (!three_sum.empty()) {
      three_sum.push_back(A[i]);
      return three_sum;
    }
  }
  return {};
}

int main(int argc, char** argv) {   
  
  vector<int> A{12, 3, 4, 1, 6, 9, 21};
  vector<int> B{1, 7, 7, 1};

  auto vec = GetThreeSum(A, 24);
  for (int x : vec) {
    cout << x << " ";
  }
  cout << endl;
  
  vec = GetThreeSum(B, 9);
  for (int x : vec) {
    cout << x << " ";
  }
  if (vec.empty()) cout << "EMPTY ARRAY" << endl;
  cout << endl;

  return 0;
}


