/*
* LongestSubarrayDistinctEntries.cpp
* -----------------
*
* Chapter 13 Question 10
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::istringstream;
using std::list;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

int LongestSubarrayWithDistinctEntriesClean(const vector<int>& A) {
  unordered_map<int, size_t> most_recent_occurrence;
  size_t longest_dup_free_subarray_start_idx = 0, result = 0;

  for (size_t i = 0; i < A.size(); ++i) {
    auto dup_idx = most_recent_occurrence[A[i]];
    if (dup_idx) {
      dup_idx--; //idx's are incremented by 1 in map to avoid zero value errors
      if (dup_idx >= longest_dup_free_subarray_start_idx) {
        result = std::max(result, i - longest_dup_free_subarray_start_idx);
        longest_dup_free_subarray_start_idx = dup_idx + 1;
      }
    }

    most_recent_occurrence[A[i]] = i + 1;
  }
  result = std::max(result, A.size() - longest_dup_free_subarray_start_idx);
  return result;
}

int LongestSubarrayWithDistinctEntries(const vector<int>& A) {
  unordered_map<int, int> element_to_idx;
  int dist = 0;
  int start_subarray = 0;
  for (int i = 0; i < A.size(); i++) {

    if (!element_to_idx.count(A[i])) {
      element_to_idx[A[i]] = i;
      dist = std::max(dist, (int) element_to_idx.size());
    } else {
      int new_start_idx = element_to_idx[A[i]] + 1;
      int idx_to_remove = new_start_idx - 1;

      while (idx_to_remove >= start_subarray) {
        element_to_idx.erase(A[idx_to_remove]);
        idx_to_remove--;
      }
      
      element_to_idx[A[i]] = i;
      start_subarray = new_start_idx;
    }

  }
  return dist;
}

int main(int argc, char** argv) {    
  vector<int> A{1, 2, 1, 3, 4, 5, 0, -3, 6};


  int result = LongestSubarrayWithDistinctEntriesClean(A);
  
  cout << result << endl;

  return 0;
}
