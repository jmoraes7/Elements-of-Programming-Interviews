/*
* FindMissingAndDuplicate.cpp
* -----------------
*
* Chapter 12 Question 12
*/

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

struct Result {
  int duplicate, missing;
};

int factorial(int x) {
  int prod = 1;
  for (int i = 1; i <= x; i++) {
    prod *= i;
  }
  return prod;
}

/*
* A must contain elements from 1 ... n; 
* It can't contain zero
*/
Result FindDuplicateMissing(const vector<int>& A) {
  int n = A.size();
  double expected_sum = (n * (n + 1)) / 2;
  double expected_prod = factorial(n);

  double actual_sum = 0, actual_prod = 1;
  for (int i = 0; i < A.size(); i++) {
    actual_sum += A[i];
    actual_prod *= A[i];
  }

  // cout << "expected_sum: " << expected_sum << endl;
  // cout << "expected_prod: " << expected_prod << endl;
  // cout << "actual_sum: " << actual_sum << endl;
  // cout << "actual_prod: " << actual_prod << endl << endl;

  double ratio_dup_to_missing =  expected_prod / actual_prod;
  
  int duplicate =  (expected_sum - actual_sum) / (ratio_dup_to_missing - 1);

  int missing = expected_sum - actual_sum + duplicate;

  return {(int) duplicate, missing};
}

/*
* A must contain elements from 1 ... n; 
* It can't contain zero
*/
Result FindDuplicateMissingAlternative(vector<int>& A) {
  int missing = -1, dup = -1;
  for (int i = 0; i < A.size(); i++) {
    if (A[abs(A[i]) - 1] > 0 ) {
      A[abs(A[i]) - 1] *= -1;
    } else {
      dup = abs(A[i]);
    }
  }

  for (int i = 0; i < A.size(); i++) {
    if (A[i] > 0) {
      missing = i + 1;
      break;
    }
  }

  return {dup, missing};
}

Result FindDuplicateMissingXOR(const vector<int>& A) {
  int XOR_val = 0;

  for (int i = 0; i < A.size(); i++) {
    XOR_val ^= i ^ A[i];
  }

  //Find bit that's set to 1 in XOR_val
  int left_most_bit = XOR_val & ~(XOR_val - 1);
  int miss_or_dup = 0;
  for (int i = 0; i < A.size(); i++) {
    //Focus on entries and numbers in which the left_most_bit'th is 1
    if (i & left_most_bit) {
      miss_or_dup ^= i;
    }
    if (A[i] & left_most_bit) {
      miss_or_dup ^= A[i];
    }
  }

  for (int i = 0; i < A.size(); i++) {
    //miss_or_dup is dup
    if (A[i] == miss_or_dup) {
      return { miss_or_dup, (miss_or_dup ^ XOR_val)};
    }
  }

  return {(miss_or_dup ^ XOR_val), miss_or_dup};
}

void SimpleTest() {
  vector<int> A{0, 1, 2, 4, 5, 6, 6};
  auto ans = FindDuplicateMissingXOR(A);
  assert(ans.duplicate == 6 && ans.missing == 3);
  // 000 001 010 011 100 100 110
  A = {0, 0, 1};
  ans = FindDuplicateMissingXOR(A);
  assert(ans.duplicate == 0 && ans.missing == 2);

  A = {1, 3, 2, 5, 3, 4};
  ans = FindDuplicateMissingXOR(A);
  assert(ans.duplicate == 3 && ans.missing == 0);
}

int main(int argc, char** argv) {
  SimpleTest(); 
  vector<int> A{1, 2, 3, 4, -8, -7, -5, -6, 6};

  Result result = FindDuplicateMissingAlternative(A);
  cout << "Missing: " << result.missing << endl;
  cout << "Duplicate: " << result.duplicate << endl;

  return 0;
}
