/*
* ClosestEntriesIn3SortedArrays.cpp
* -----------------
*
* Chapter 15 Question 7
*/
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <map>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::unique_ptr;

int ClosestEntriesInSortedArrays (vector<vector<int> > sorted_arrays) {
  int min_distance_so_far = numeric_limits<int>::max();

  struct IterTail {
    vector<int>::const_iterator iter, tail;
  };
  // Stores two iterators in each entry. One for traversing, and the other to
  // check we reach the end.
  multimap<int, IterTail> iter_and_tail;
  for (const vector<int>& sorted_array : sorted_arrays) {
    iter_and_tail.emplace(
        sorted_array.front(),
        IterTail{sorted_array.cbegin(), sorted_array.cend()});
  }

  while (true) {
    int min_value = iter_and_tail.cbegin()->first,
        max_value = iter_and_tail.crbegin()->first;
    min_distance_so_far = min(max_value - min_value, min_distance_so_far);
    const auto next_min = next(iter_and_tail.cbegin()->second.iter),
               next_end = iter_and_tail.cbegin()->second.tail;
    // Return if some array has no remaining elements.
    if (next_min == next_end) {
      return min_distance_so_far;
    }
    iter_and_tail.emplace(*next_min, IterTail{next_min, next_end});
    iter_and_tail.erase(iter_and_tail.cbegin());
  }  
}

int main(int argc, char** argv) {    

  vector<vector<int> > entries = {{5,10,15}, {3,6,9,12,15}, {8,16,24}};

  cout << ClosestEntriesInSortedArrays(entries) << endl;
  return 0;
}
