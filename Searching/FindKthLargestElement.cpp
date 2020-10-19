/*
* FindKthLargestElement.cpp
* -----------------
*
* Chapter 12 Question 9
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

void PrintList(vector<int> A) {
  for (int x : A) { 
    cout << x << " ";
  }
  cout << endl;
}
int partitionArrayClean(vector<int>& A, int pivot_idx, int left, int right) {
  // 3, 2, 1, 5, 4
  // i = 3, idx = 3
  int pivot_value = A[pivot_idx];
  int new_pivot_idx = left;
  std::swap(A[pivot_idx], A[right]);

  for (int i = left; i < right; ++i) {
    if (A[i] < pivot_value) {
      cout << "i = " << i << " PIVOT VAL: " << pivot_value << " New Pivot Idx = " << new_pivot_idx << endl;
      PrintList(A);
      std::swap(A[i], A[new_pivot_idx++]);
      PrintList(A);
      cout << endl;
    }
  }

  std::swap(A[right], A[new_pivot_idx]);
  cout << "FINAL: ";
  PrintList(A);
  cout << endl;

  return new_pivot_idx;

}

int partitionArray(vector<int>& A, int pivot_idx, int left, int right) {
  std::swap(A[pivot_idx], A[left]);

  int pivot = A[pivot_idx];
  while (left < right) {
    if (A[left + 1] <= A[left]) {
      std::swap(A[left], A[left + 1]);
      left++;
    } else {
      std::swap(A[left + 1], A[right]);
      right--;
    }
  }
  
  return left;
}

int FindKthLargest(vector<int> A, int k) {
  int left = 0, right = A.size() - 1;
  default_random_engine gen((random_device())());
  
  while (left <= right) {
    uniform_int_distribution<int> dis(left, right);
    int pivot_idx = dis(gen);
    int new_pivot_idx = partitionArrayClean(A, pivot_idx, left, right);

    if (new_pivot_idx == k - 1) {
      return A[new_pivot_idx];
    } else if (new_pivot_idx >= k) {
      right = new_pivot_idx - 1;
    } else {
      left = new_pivot_idx + 1;
    }
  }

  return -1;
}

int main(int argc, char** argv) {
  vector<int> A{3, 2, 1, 5, 4};


  cout << FindKthLargest(A, 2);
  return 0;
}
