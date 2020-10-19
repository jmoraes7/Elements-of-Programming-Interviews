/*
* SortApproximatelySortedData.cpp
* -----------------
*
* Chapter 11 Question 3
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

using namespace std;

static vector<int> result;

vector<int> SortApproximatelySortedData(istringstream* sequence, int k) {
  priority_queue<int, vector<int>, greater<int> > min_heap;
  vector<int> result;
  
  int x;
  for (int i = 0; i < k && *sequence >> x; ++i) {
    min_heap.push(x);
  }

  while (*sequence >> x) {
    min_heap.push(x);
    
    result.push_back(min_heap.top());

    min_heap.pop();
  }

  //sequence is exhausted, extract remaining elements in min heap
  while (!min_heap.empty()) {
    result.push_back(min_heap.top());
    min_heap.pop();
  }

  return result;
}

// It should sort to 1, 2, 3, 4, 5, 6, 7, 8, 9.
void SimpleTest() {
  vector<int> A{2, 1, 5, 4, 3, 9, 8, 7, 6};
  stringstream ss;
  for (int a : A) {
    ss << a << ' ';
  }
  istringstream sequence(ss.str());
  vector<int> result = SortApproximatelySortedData(&sequence, 3);
  vector<int> golden_result{1, 2, 3, 4, 5, 6, 7, 8, 9};
  assert(equal(result.begin(), result.end(), golden_result.begin(),
               golden_result.end()));
}

int main(int argc, char* argv[]) {
  SimpleTest();

  return 0;
}