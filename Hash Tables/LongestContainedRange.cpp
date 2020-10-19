/*
* LongestContainedRange.cpp
* -----------------
*
* Chapter 13 Question 11
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

int FindLongestContainedRange(const vector<int>& A) {

  unordered_set<int> elements;
  for (int num : A) {
    elements.insert(num);
  }

  int max_range = 0;
  for (auto it : elements) {
    int range = 1;

    int lower_range_elem = it - 1;
    while (elements.count(lower_range_elem)) {
      elements.erase(lower_range_elem);
      lower_range_elem--;
      range++;
    }

    int upper_range_elem = it + 1;
    while (elements.count(upper_range_elem)) {
      elements.erase(upper_range_elem);
      upper_range_elem++;
      range++;
    }
  
    elements.erase(it);

    max_range = std::max(max_range, range);
  }

  return max_range;
}

int main(int argc, char** argv) {    
  vector<int> A{3, -2, 7, 9, 8, 1, 2, 0, -1, 5, 8, 9, -3};

  int result = FindLongestContainedRange(A);
  
  cout << result << endl;

  return 0;
}
