/*
* CountStepsInBoardGame.cpp
* -----------------
*
* Chapter 17 Question 11
*/

#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <list>
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
using std::list;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::tuple;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

int NumberOfStepsHelper(int n, int k, vector<int>* T) {
  if (n < 0) return 0;
  if (n == 0 || n == 1) return 1;

  if ((*T)[n] != 0) {
    return (*T)[n];
  }

  for (int i = 1; i <= k; i++) {
    (*T)[n] += NumberOfStepsHelper(n - i, k, T);
  }

  return (*T)[n];
}


int NumberOfStepsTopDown(int n, int k) {
  vector<int> T(n + 1, 0);
  T[0] = T[1] = 1;

  return NumberOfStepsHelper(n, k, &T);
}

int NumberOfStepsBottomUp(int n, int k) {

  vector<int> steps(n+1, 0);
  steps[0] = steps[1] = 1;
  for (int i = 2; i <= n; i++) {
    // steps[i] =0;
    for (int j = 1; j <= k && i - j >=0; j++) {
      steps[i] += steps[i - j];
    }
  }
  return steps[n];
}

/*
* Sliding Window Solution
*/
int NumberOfStepsLinearSolution(int n, int k) {

  vector<int> steps(n+1, 0);
  steps[0] = 1;

  int temp_num_steps;
  for (int i = 1; i <= n; i++) {
    int idx_not_in_window = i - k - 1;
    int idx_now_in_window = i - 1;
    if (idx_not_in_window >= 0) {
      temp_num_steps -= steps[idx_not_in_window];
    }
    temp_num_steps += steps[idx_now_in_window];
    steps[i] = temp_num_steps;
  }
  return steps[n];
}

int main(int argc, char** argv) {   
  

  int n = 4, k = 3;

  cout << NumberOfStepsTopDown(n, k) << " " << NumberOfStepsBottomUp(n, k) <<
              " " << NumberOfStepsLinearSolution(n, k);

  return 0;
}

