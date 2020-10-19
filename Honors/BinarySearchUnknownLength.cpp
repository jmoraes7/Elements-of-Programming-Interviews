/*
* BinarySearchUnknownLength.cpp
* -----------------
*
* Chapter 22 Question 18
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::stoi;
using std::vector;

int BinarySearchUnknownLength(const vector<int>& A, int k) {
  int p = 0;
  int count = 0;
  while (true) {
    try {
      int idx = (1 << p) - 1; //2^p - 1
      cout << idx << endl;
      if (A.at(idx) == k) {
        return idx;
      } else if (A.at(idx) > k) {
        break;
      }
    } catch (const exception& e) {
      break;
    }
    p++;
  }

  int left = (1 << (p - 1)), right = (1 << p) - 2;
  cout << p << " " << left << " " << right << endl;
  while (left <= right) {
    int mid = left + ((right - left) / 2);
    
    try {
      if (A.at(mid) == k) {
        return mid;
      } else if (A.at(mid) > k) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }

    } catch (const exception& e) {
      right = mid - 1;
    }
  }

  return -1;
}

int main(int argc, char** argv) {   
  
  vector<int> A{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
  int k = 23;

  cout << BinarySearchUnknownLength(A, k) << endl;

  return 0;
}


