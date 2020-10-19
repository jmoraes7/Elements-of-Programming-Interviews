/*
* PlanFishingTrip.cpp
* -----------------
*
* Chapter 17 Question 4
*/
#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

int MaximizeFishing(vector<vector<int> > A) {  
  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < A[0].size(); j++) {
      A[i][j] += std::max( i < 1 ? 0 : A[i-1][j], j < 1 ? 0 : A[i][j-1]);
    }
  }
  return A.back().back();
}

int main(int argc, char** argv) {   
  
  std::default_random_engine gen((random_device())());
  int n = 3, m = 3;
  vector<vector<int> > A(n, vector<int>(m));
  
  A[0][2] = 2;
  A[1][1] = 1;
  A[2][1] = 2;
  A[1][2] = 2;
  A[2][2] = 3;

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      cout << A[i][j] << ' ';
    }
    cout << endl;
  }
  cout << MaximizeFishing(A) << endl;

  return 0;
}

