/*
* GetArrayEntryEqualToIndex.cpp
* -----------------
*
* Chapter 12 Question 3
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
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

int getMagicIndexHelper(vector<int> A, int start, int end) {
  if (start > end) {
    return -1;
  }s

  int mid = start + ((end - start) / 2);
  
  if (A[mid] == mid) {
    return mid;
  }

  //search left side of array
  int left = getMagicIndexHelper(A, start, std::min(A[mid], mid - 1));

  //if element found in left subarray
  if (left >= 0) {
    return left;
  }

  //search right side of array
  return getMagicIndexHelper(A, std::max(A[mid], mid + 1), end);
}

int GetArrayEntryEqualToIndexWithDups(vector<int> A) {
  return getMagicIndexHelper(A, 0, A.size() - 1);
}

int GetArrayEntryEqualToIndex(vector<int> A) {
  int left = 0, right = A.size() - 1;

  while (left <= right) {
    int mid = left + ((right - left) / 2);

    cout << A[mid] << " " << mid << endl;

    if (A[mid] < mid) {
      left = mid + 1;
    } else if (A[mid] > mid) {
      right = mid - 1;
    } else {
      return mid;
    }
  }
  
  return -1;
}

int main(int argc, char** argv) {

  //vector<int> arr{-2, 0, 2, 4, 6, 7, 9};
  vector<int> arr {-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13}; //{-2, 0, 1, 4, 5, 5, 5};


  //arr[mid = 5] = 3 , diff = 3 - 5 = -2

  int target_idx = GetArrayEntryEqualToIndexWithDups(arr); //SearchFirstOfKNaive(arr, 285);

  cout << "Final Index: " << target_idx << endl;

  return 0;
}
