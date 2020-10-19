/*
* SearchCyclicallySortedArray.cpp
* -----------------
*
* Chapter 12 Question 4
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

int getSmallestElement(vector<int> A) {
  int left = 0, right = A.size() - 1;
  int count = 0;
  while (left < right) {
    int mid = left + ((right - left) / 2);

    cout << "LEFT: " << left << " RIGHT: " << right << " MID: " << mid << " ELEMENT: " << A[mid] << endl;

    if (A[mid] > A[right]) {
      left = mid + 1;
    } else {
      right = mid;
    }
    count++;
    if (count == 10) { return -1; }
  }
  
  return left;
}

int main(int argc, char** argv) {

  vector<int> arr {378, 478, 550, 631, 103, 203, 220, 234, 279, 368};

  vector<int> A {4, 6, 8, 2, 3};

  int target_idx = getSmallestElement(arr);

  cout << "Final Index: " << target_idx << endl;

  return 0;
}
