/*
* SearchInTwoSortedArrays.cpp
* -----------------
*
* Chapter 22 Question 19
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

int GetFirstElementLessThanK(vector<int>& A, int start, int end, int target) {
  int idx = -1;
  
  while (start <= end) {
    int mid = start + ((end - start) / 2);
    if (A[mid] >= target) {
      end = mid - 1;
    } else {
      idx = mid;
      start = mid + 1;
    }
  } 

  return idx;
}

int SearchInTwoSortedArrays(vector<int>& A, vector<int>& B, int k) {
  int A_i = 0, A_j = std::min(static_cast<int>(A.size()) - 1, k - 1);
  int B_i = 0, B_j = std::min(static_cast<int>(B.size()) - 1, k - 1);

  bool last_removed_from_A = false;

  while ((A_j - A_i + 1) + (B_j - B_i + 1) > k) {
    
    if (A[A_j] < B[B_j]) {
      B_j = GetFirstElementLessThanK(B, B_i, B_j, A[A_j]);
      last_removed_from_A = false;
    } else {
      A_j = GetFirstElementLessThanK(A, A_i, A_j, B[B_j]);
      last_removed_from_A = true;
    }
  }

  while ((A_j - A_i + 1) + (B_j - B_i + 1) != k) {
    if (last_removed_from_A) {
      A_j++;
    } else {
      B_j++;
    }
  }

  if (A_j == -1) return B[B_j];
  if (B_j == -1) return A[A_j];

  return std::max(A[A_j], B[B_j]);
}

int SearchInTwoSortedArraysClean(vector<int>& A, vector<int>& B, int k) {
  int A_start = 0, A_end = std::min(static_cast<int>(A.size() - 1), k - 1);
  int B_start = 0, B_end = std::min(static_cast<int>(B.size() - 1), k - 1);
  int count = 0;
  int mid_a, mid_b;
  while (true) {
    mid_a = A_start + ((A_end - A_start) / 2);
    mid_b = B_start + ((B_end - B_start) / 2);

    // cout << mid_a << " " << mid_b << endl;
    if (mid_a + mid_b + 2 > k) {
      if (A[mid_a] >= B[mid_b]) {
        A_end = mid_a - 1;
      } else {  
        B_end = mid_b - 1;
      }
    } else if (mid_a + mid_b + 2 < k) {
      if (A[mid_a] < B[mid_b]) {
        A_start = mid_a + 1;
      } else {
        B_start = mid_b + 1;
      }
    } else {
      if (A[mid_a] == B[mid_b]) return A[mid_a];

      if (A[mid_a] < B[mid_b]) {

        if (mid_a == A.size() - 1 || A[mid_a + 1] > B[mid_b]) {
          return B[mid_b];
        } else {
          A_start = mid_a + 1;
          B_end = mid_b - 1;
        }

      } else if (A[mid_a] > B[mid_b]) {
        if (mid_b == B.size() - 1 || B[mid_b + 1] > A[mid_a]) {
          // cout << "HERE HERE HERE " << mid_a << " " << A[mid_a]<< endl;
          return A[mid_a];
        } else {
          A_end = mid_a - 1;
          B_start = mid_b + 1;
        }
      }
    }

    if (A_start > A_end) {
      cout << "A ended " << A_start << endl;
      return B[k - A_start - 1];
    } 

    if (B_start > B_end) {
      cout << "B ended " << B_start << endl;
      return A[k - B_start - 1];
    }
  }
  cout << "Here" << endl;
  cout << mid_a << " " << mid_b << endl;

  return std::max(A[mid_a], B[mid_b]);
}

int main(int argc, char** argv) {   
  vector<int> A{1, 2, 3, 4, 7, 8, 9, 10};
  vector<int> B{-10, -5, -3}; //7, 7, 11, 15, 18, 20};
  int k = 11;
  //10 - A-start

  // 1 2 3 4 5 6
  // -2 3 4 
  int result = SearchInTwoSortedArraysClean(A, B, k);
  cout << "RESULT: " << result << endl;

  return 0;
}


