/*
* LongestContiguousIncreasingSubarray.cpp
* -----------------
*
* Chapter 22 Question 5
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::array;
using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::random_device;
using std::stoul;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

std::pair<int, int> LongestContiguousIncreasingSubarray(vector<int> A) {
  std::pair<int, int> indices = {-1, -1};

  int max_len_idx = 0;
  int max_len = 0;
  int curr_len = 1;
  for (int i = 1; i < A.size(); i++) {
    if (A[i] <= A[i - 1]) {
      if (curr_len > max_len) {
        max_len = curr_len;
        max_len_idx = i - 1;
      }

      curr_len = 1;
    } else {
      curr_len++;
    }
    // cout << i << " curr_len: " << curr_len << endl;

  } 

  if (curr_len > max_len) {
    max_len_idx = A.size() - 1;
    max_len = curr_len;
  }

  // cout << max_len_idx << " " << curr_len << endl;
  return {max_len_idx - max_len + 1, max_len_idx};
}

int main(int argc, char** argv) {   
  
  vector<int> A = {2, 11, 3, 5, 13, 7, 19, 17, 23};

  auto res = LongestContiguousIncreasingSubarray(A);
  cout << res.first << " " << res.second << endl;

  return 0;
}


