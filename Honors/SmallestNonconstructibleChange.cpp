/*
* SmallestNonconstructibleChange.cpp
* -----------------
*
* Chapter 22 Question 24
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
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

int SmallestNonconstructibleValue(vector<int>& A) {
  int max_denomination = 0;
  for (int i = 0; i < A.size(); i++) {
    max_denomination += A[i];
  }

  vector<bool> partial_sums(max_denomination + 1, false);
  partial_sums[0] = true;
  for (int num : A) {
    for (int j = partial_sums.size() - 1; j >= num; j--) {
      if (partial_sums[j - num]) {
        partial_sums[j] = true;
      }
    } 
  }

  for (int i = 0; i < partial_sums.size(); i++) {
    if (!partial_sums[i]) {
      return i;
    }
  }
  return max_denomination + 1;
}

int SmallestNonconstructibleValueClean(vector<int>& A) {
  sort(A.begin(), A.end());
  int max_constructible_val = 0;
  for (int& a : A) {
    if (a > max_constructible_val + 1) {
      break;
    } 
    max_constructible_val += a;
  }

  return max_constructible_val + 1;
}


int main(int argc, char** argv) {   
  vector<int> coins{1, 1, 1, 1, 1, 5, 10, 25};
  vector<int> coins2{12, 2, 1, 15, 2 , 4};
  cout << SmallestNonconstructibleValue(coins2) << endl;
  
  return 0;
}


