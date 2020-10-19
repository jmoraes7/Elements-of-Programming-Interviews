/*
* ComputeKLargestElementsInHeap.cpp
* -----------------
*
* Chapter 11 Question 6
*/

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::greater;
using std::istringstream;
using std::less;
using std::priority_queue;
using std::random_device;
using std::string;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

struct HeapEntry {
  public:
    bool operator<(const HeapEntry& that) const {
      return val < that.val;
    }

    int idx, val;
};

vector<int> KLargestInBinaryHeap(vector<int>& A, int k) {
  if (k <= 0) { return vector<int>(); }

  
  priority_queue<HeapEntry, vector<HeapEntry> > max_heap;
  vector<int> result;
  max_heap.push(HeapEntry{0, A[0]});
  for (int i = 0; i < k; ++i) {

    result.push_back(max_heap.top().val);
    int idx = max_heap.top().idx;
    max_heap.pop();

    int right_child_idx = 2 * idx + 1;
    if (right_child_idx < A.size()) {
      max_heap.push(HeapEntry{right_child_idx, A[right_child_idx]});
    }

    int left_child_idx = 2 * idx + 2;
    if (left_child_idx < A.size()) {
      max_heap.push(HeapEntry{left_child_idx, A[left_child_idx]});
    }
  }
  
  return result;
}

int main(int argc, char* argv[]) {

  int x = log2(3);
  cout << x << endl;
  vector<int> max_heap{10, 2, 9, 2, 2, 8, 8, 2, 2, 2, 2, 7, 7, 7, 7};

  auto result = KLargestInBinaryHeap(max_heap, 4);
  vector<int> expected_result{10, 9, 8, 8};

  assert(equal(result.begin(), result.end(), expected_result.begin(),
               expected_result.end()));
  result = KLargestInBinaryHeap(max_heap, 5);
  expected_result = {10, 9, 8, 8, 7};
  assert(equal(result.begin(), result.end(), expected_result.begin(),
               expected_result.end()));

  max_heap = {97, 84, 93, 83, 81, 90, 79, 83, 55, 42, 21, 73};
  result = KLargestInBinaryHeap(max_heap, 3);
  expected_result = {97, 93, 90};
  assert(equal(result.begin(), result.end(), expected_result.begin(),
               expected_result.end()));

  max_heap = {100, 1, 5, 0, 0};
  result = KLargestInBinaryHeap(max_heap, 1);
  expected_result = {100};
  assert(equal(result.begin(), result.end(), expected_result.begin(),
               expected_result.end()));
  return 0;
}