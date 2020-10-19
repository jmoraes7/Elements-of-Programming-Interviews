/*
* LongestNondecreasingSubsequence.cpp
* -----------------
*
* Chapter 17 Question 14
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_real_distribution;
using std::string;
using std::vector;

vector<int> getLongestSubsequence(const vector<int>& A) {
  if (A.empty()) { 
    return {};
  }

  int max_length_idx = 0;
  vector<int> longest_lengths(A.size(), 0);
  longest_lengths[0] = 1;

  for (int i = 1; i < A.size(); i++) {
    
    for (int j = i - 1; j >= 0; j--) {
      if (A[j] <= A[i]) {
        longest_lengths[i] = std::max(longest_lengths[i], longest_lengths[j]);
      }
    }
    longest_lengths[i]++;

    if (longest_lengths[i] > longest_lengths[max_length_idx]) {
      max_length_idx = i;
    }
  }
  
  int max_length = longest_lengths[max_length_idx];
  vector<int> subsequence(max_length);
  for (int i = max_length_idx; i >= 0 && max_length > 0; i--) {
    if (longest_lengths[i] == max_length) {
      subsequence[--max_length] = A[i];
    }
  }

  return subsequence;
}

int main(int argc, char** argv) {   
  
  vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9};

  vector<int> subsequence = getLongestSubsequence(arr);

  for (int x : subsequence) {
    cout << x << " ";
  }
  cout << endl;

  return 0;
}

