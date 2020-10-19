/*
* MaxTrappedWaterArea.cpp
* -----------------
*
* Chapter 18 Question 8
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

int GetMaxArea(vector<int>& heights) {
  int max_area = 0;

  int i = 0, j = heights.size() - 1;

  while (i < j) {
    int candidate_area = std::min(heights[i], heights[j]) * (j - i);
    max_area = std::max(max_area, candidate_area);

    if (heights[i] > heights[j]) {
      j--;
    } else if (heights[i] < heights[j]) {
      i++;
    } else {
      i++, j--;
    }
  }
  return max_area;
}

int main(int argc, char** argv) {   
  vector<int> A = {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1};

  cout << GetMaxArea(A) << endl;

  return 0;
}


