/*
* MaxTrappedWaterArea.cpp
* -----------------
*
* Chapter 18 Question 9
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::stack;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

struct Rectangle {
  int height, start_idx;
};

int getMaxArea(stack<Rectangle>* stack, int curr_height, int end_idx) {
  int max_area = 0;

  while (!(*stack).empty() && (*stack).top().height > curr_height) {
    Rectangle r = (*stack).top();
    max_area = std::max(max_area, r.height * (end_idx - r.start_idx));
    (*stack).pop();
  }

  return max_area;
}

int CalculateLargestRectangle(vector<int>& heights) {
  stack<Rectangle> stack;

  int max_area = 0;
  for (int i = 0; i < heights.size(); i++) {
    int height = heights[i];
  
    if (!stack.empty() && height < stack.top().height) {
      max_area = std::max(max_area, getMaxArea(&stack, height, i));
    }

    if (stack.empty() || height != stack.top().height) {
      Rectangle rect{height, i};
      stack.push(rect);
    }
  }

  max_area = std::max(max_area, getMaxArea(&stack, 0, heights.size()));

  return max_area;
}

int CalculateLargestRectangleClean(vector<int>& heights) {

}

int main(int argc, char** argv) {   
  vector<int> A = {2, 3, 4, 1, 2, 3, 11, 2, 2, 2, 15};
  vector<int> B = {1, 3, 3, 3, 4, 4, 4, 4, 4, 3, 6, 6, 6, 3, 3, 2, 2, 1};

  cout << CalculateLargestRectangle(B) << " " << CalculateLargestRectangleClean(B) << endl;

  return 0;
}


