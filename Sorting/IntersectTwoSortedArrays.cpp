/*
* IntersectTwoSortedArrays.cpp
* -----------------
*
* Chapter 14 Question 1
*/

#include <algorithm>
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
using std::numeric_limits;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

vector<int> IntersectSortedArraysDiffLengths(vector<int> A, vector<int> B) {
  vector<int> intersection;

  auto shorter = A.size() < B.size() ? A : B;
  auto longer = A.size() < B.size() ? B : A;

  for (int i = 0; i < shorter.size(); ++i) {
    if ((i == 0 || shorter[i] != shorter[i - 1]) && std::binary_search(longer.cbegin(), longer.cend(), shorter[i])) {
      intersection.push_back(shorter[i]);
    }
  }

  return intersection;
}

vector<int> IntersectSortedArrays(vector<int> A, vector<int> B) {
  int i = 0, j = 0;
  vector<int> intersection;

  while (i < A.size() && j < B.size()) {
    if (A[i] == B[j] && (i == 0 || (A[i] != A[i - 1]))) {
      intersection.push_back(A[i]);
      ++i, ++j;
    } else if (A[i] < B[j]) {
      ++i;
    } else {
      ++j;
    }
  }
  return intersection;
}

int main(int argc, char** argv) {
  vector<int> A{2, 3, 3, 5, 5, 6, 7, 7, 8, 12};
  vector<int> B{5, 5, 6, 8, 8, 9, 10, 10};

  vector<int> intersection = IntersectSortedArrays(A, B);

  for (int x : intersection) {
    cout << x << " "; 
  }
  cout << endl;
  return 0;
}
