/*
* IntersectTwoSortedArrays.cpp
* -----------------
*
* Chapter 14 Question 2
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

vector<int> MergeTwoSortedArrays(vector<int> A, int m, vector<int> B, int n) {
  int a = m - 1, b = n - 1, write_idx = m + n - 1;

  while (a >= 0 && b >= 0) {
    A[write_idx--] = A[a] < B[b] ? B[b--] : A[a--];
  }

  while (b >= 0) {
    A[write_idx--] = B[b--];
  }

  return A;
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
