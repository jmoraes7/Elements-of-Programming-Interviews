/*
* SearchForFirstOccurenceOfK.cpp
* -----------------
*
* Chapter 12 Question 1
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

int BinarySearch(vector<int> arr, int target) {
  
  int left = 0, right = arr.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] < target) {
      left = mid + 1;
    } else if (arr[mid] > target) {
      right = mid - 1;
    } else {
      return mid;
    }
  }

  return -1;
}

int SearchFirstOfKNaive(vector<int> A, int k) {
  int idx = BinarySearch(A, k);
  cout << "Intial index: " << idx << endl;

  while (A[idx] == k && idx > 0) {
    idx--;
  }

  return idx + 1;
}

int SearchFirstOfK(vector<int> A, int k) {
  int left = 0, right = A.size() - 1, result = -1;

  while (left <= right) {
    int mid = left + ((right - left) / 2);

    if (A[mid] < k) {
      left = mid + 1;
    } else if (A[mid] > k) {
      right = mid - 1;
    } else {
      result = mid;
      right = mid - 1;
    }
  }

  return result;
}

int main(int argc, char** argv) {

  vector<int> arr{-14, -10, 2, 108, 108, 243, 285, 285, 285, 401};

  int target_idx = SearchFirstOfK(arr, 285); //SearchFirstOfKNaive(arr, 285);

  cout << "Final Index: " << target_idx << endl;

  return 0;
}
