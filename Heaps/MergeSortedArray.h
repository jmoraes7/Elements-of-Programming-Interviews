#ifndef MERGE_SORTED_ARRAY_H
#define MERGE_SORTED_ARRAY_H

#include <cassert>
#include <iostream>
#include <list>
#include <queue>
#include <iterator>

#include <vector>

using namespace std;

struct IteratorCurrentAndEnd {
  bool operator<(const IteratorCurrentAndEnd& that) const {
    return *current > *that.current;
  }

  vector<int>::const_iterator current;
  vector<int>::const_iterator end;
};

vector<int> MergeSortedArrays(const vector<vector<int> >& sorted_arrays) {
  priority_queue<IteratorCurrentAndEnd, vector<IteratorCurrentAndEnd> > min_heap;

  for (const auto& sorted_array : sorted_arrays) {
    min_heap.push( 
      IteratorCurrentAndEnd{sorted_array.cbegin(), sorted_array.cend()}
    );
  }

  vector<int> result;
  while (!min_heap.empty()) {
    auto smallest_array = min_heap.top();
    min_heap.pop();

    if (smallest_array.current != smallest_array.end) {

      result.push_back(*smallest_array.current);

      min_heap.push(IteratorCurrentAndEnd{
        next(smallest_array.current), smallest_array.end
      });
    }
  }

  return result;
}

#endif