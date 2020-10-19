/*
* KthLargestElementLargeNSmallK.cpp
* -----------------
*
* Chapter 22 Question 20
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string> 
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::greater;
using std::istringstream;
using std::length_error;
using std::make_shared;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::stringstream;
using std::stoi;
using std::vector;

int FindKthLargestUnknownLength(istringstream* sin, int k) {
  vector<int> candidates;

  int x;
  while (*sin >> x) {
    candidates.emplace_back(x);
    if (candidates.size() == 2 * k - 1) {
      nth_element(candidates.begin(), candidates.begin() + k - 1,
        candidates.end(), greater<int>());
      candidates.resize(k);
    }
  }

  nth_element(candidates.begin(), candidates.begin() + k - 1, 
    candidates.end(), greater<int>());

  return candidates[k-1];
}

static void SimpleTestArray(vector<int> A) {
  stringstream ss;
  for (int a : A) {
    ss << a << ' ';
  }
  for (int i = 0; i < A.size(); ++i) {
    cout << "i = " << i << endl;
    istringstream sin(ss.str());
    int k = i + 1;
    int result = FindKthLargestUnknownLength(&sin, k);
    nth_element(A.begin(), A.begin() + A.size() - k, A.end());
    assert(result == A[A.size() - k]);
  }
}

int main(int argc, char** argv) {   
  vector<int> A{1, 2, 3, 4, 7, 8, 9, 10};
  vector<int> B{-10, -5, -3}; //7, 7, 11, 15, 18, 20};
  int k = 11;

  SimpleTestArray(A);

  return 0;
}


