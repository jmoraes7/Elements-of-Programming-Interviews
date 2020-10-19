/*
* GetFirstElementGreaterThanK.cpp
* -----------------
*
* Chapter 12 Question 2
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

int GetFirstElementGreaterThanK(vector<int> A, int k) {
  int left = 0, right = A.size() - 1, result = -1;

  while (left <= right) {
    int mid = left + ((right - left) / 2);
   if (A[mid] > k) {
      result = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return result;
}


int main(int argc, char** argv) {

  vector<int> arr{-14, -10, 2, 108, 108, 243, 285, 285, 285, 401};

  int target_idx = GetFirstElementGreaterThanK(arr, 88); //SearchFirstOfKNaive(arr, 285);

  cout << "Final Index: " << target_idx << endl;

  return 0;
}
