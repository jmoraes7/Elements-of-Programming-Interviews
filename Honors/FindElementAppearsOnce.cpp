/*
* FindElementAppearsOnce.cpp
* -----------------
*
* Chapter 22 Question 21
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

int FindElementAppearsOnce(vector<int>& A) {

  vector<int> arr(31, 0);
  int max_idx = 0;

  for (int& num : A) {
    int idx = 0;
    while (num) {
      if (num & 1) {
        arr[idx] = (arr[idx] + 1) % 3;
      }
      num >>= 1;
      idx++;
    }

    max_idx = std::max(max_idx, idx);
  }

  cout << endl << "Max Num Digits: " << max_idx << endl;

  int missing_num = 0;
  for (int i = max_idx; i >= 0; i--) {
    missing_num <<= 1;
    missing_num += arr[i];
  }

  return missing_num;
}

int FindElementAppearsOnceClean(vector<int>& A) {
  // ones denotes whether a bit-position has been set once (modulo 3) so far.
  // twos denotes whether a bit-position has been set twice (modulo 3) so far.
  int ones = 0, twos = 0;
  int next_ones, next_twos;

  
  for (int& i : A) {
    next_ones = (~i & ones) | (i & ~ones & ~twos);
    next_twos = (i & ones) | (~i & twos);
    
    ones = next_ones, twos = next_twos;
  }

  return ones;
}

int main(int argc, char** argv) {   
  vector<int> A{2, 122, 2, 5, 2, 5, 5};

  int x = 5;

  cout << FindElementAppearsOnceClean(A);

  return 0;
}


