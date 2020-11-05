/*
* Max2DSubarraySum.cpp
* -----------------
*
* Chapter 22 Question 41
*/

#include <algorithm>
#include <cassert>
#include <cmath>
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
using std::get;
using std::hash;
using std::numeric_limits;
using std::ostream;
using std::random_device;
using std::stack;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

int getMaxSubarraySum(vector<int>& A) {
  int max_sum = numeric_limits<int>::min(), curr = 0;
  for (int i = 0; i < A.size(); i++) {
    curr = std::max(A[i], curr + A[i]);
    max_sum = std::max(max_sum, curr);
  }
  return max_sum;
}

int Max2DSubarraySum(vector<vector<int> >* A) {
  vector<int> running_sum(A->size(), 0);

  int sum = numeric_limits<int>::min();
  
  for (int i = 0; i < (*A)[0].size(); i++) {
    for (int j = i; j < (*A)[0].size(); j++) {

      for (int row = 0; row < A->size(); row++) {
        running_sum[row] += (*A)[row][j];        
      }

      sum = std::max(getMaxSubarraySum(running_sum), sum);
    }
    std::fill(running_sum.begin(), running_sum.end(), 0);
  }

  return sum;
}

struct MaxHW {
  int h, w;
};

int Max2DSubarraySumBookSol1(vector<vector<int> > &A) {

  vector<vector<MaxHW> > table(A.size(), vector<MaxHW>(A.front().size()));

  for (int i = A.size() - 1; i >= 0; i--) {
    for (int j = A[i].size() - 1; j >= 0; j--) {
      
      table[i][j] = A[i][j] ?
                    MaxHW{i + 1 < A.size() ? table[i + 1][j].h + 1 : 1, 
                    j + 1 < A[i].size() ? table[i][j + 1].w + 1 : 1} 
                    : MaxHW{0, 0};  
    }
  }

  int max_rect_area = 0;
  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < A[i].size(); j++) {

      if (A[i][j] && table[i][j].w * table[i][j].h > max_rect_area) {
        int min_width = numeric_limits<int>::max();
        for (int a = 0; a < table[i][j].h; a++) {
          min_width = std::min(min_width, table[i + a][j].w);
          max_rect_area = std::max(max_rect_area, min_width * (a + 1));
          // cout << max_rect_area << " " << " i: " << i << " j: " << j << " h: " << table[i][j].h  << " w: " << table[i][j].w << " area: " << min_width * (a + 1) <<  " min_width: " << min_width << " curr_width: " << table[i + a][j].w << " a: " << a + 1 << endl << endl;
        }
      }
    }
  }

  return max_rect_area;
}

int MaxSquareSubmatrix(vector<vector<int> > &A) {
  vector<vector<MaxHW> > table(A.size(), vector<MaxHW>(A.front().size()));

  for (int i = A.size() - 1; i >= 0; i--) {
    for (int j = A[i].size() - 1; j >= 0; j--) {
      table[i][j] = A[i][j] ?
                    MaxHW{i + 1 < A.size() ? table[i + 1][j].h + 1 : 1, 
                    j + 1 < A[i].size() ? table[i][j + 1].w + 1 : 1} 
                    : MaxHW{0, 0};  
    }
  }


  vector<vector<int> > s(A.size(), vector<int>(A.front().size()));
  int max_area = 0;
  for (int i = A.size() - 1; i >= 0; i-- ) {
    for (int j = A[i].size() - 1; j >= 0; j--) {
      // cout << "here" << endl;
      int side = std::min(table[i][j].h, table[i][j].w);

      if (A[i][j]) {
        if (i + 1 < A.size() && j + 1 < A[i+1].size()) {
          // cout << i << " " << j << " " << side << " " << s[i+1][j+1] << endl;
          side = std::min(side, s[i + 1][j + 1] + 1);
        }
        s[i][j] = side;
        max_area = std::max(max_area, side * side);
      }
    }
  }

  for (auto x : s) {
    for (auto y : x) {
      cout << y << " ";
    }
    cout << endl;
  }

  return max_area;
}

struct Elem {
  int val, first_idx;
};

int CalculateLargestRectangle(vector<int> heights) { 
  stack<Elem> stack;

  int max_sum = 0;
  for (int i = 0; i < heights.size(); i++ ) {
    if (stack.empty() || stack.top().val < heights[i]) {
      stack.emplace(Elem{heights[i], i});
    } 
    
    else if (stack.top().val > heights[i]){
      Elem e = {heights[i], i};
      cout << "Height: " << heights[i] << endl;
      while (!stack.empty() && stack.top().val > heights[i]) {
        cout << stack.top().val << " " << stack.top().first_idx << endl;
        e.first_idx = std::min(e.first_idx, stack.top().first_idx);
        cout << e.first_idx << endl;
        max_sum = std::max(max_sum, stack.top().val * (i - stack.top().first_idx));
        stack.pop();
      }
      stack.push(e);
      cout << endl;
    }
  }

  while (!stack.empty()) {
    int width = heights.size() - stack.top().first_idx;
    max_sum = std::max(max_sum, stack.top().val * width);
    stack.pop();
  }
  
  return max_sum;
}

int CalculateLargestRectangleClean(vector<int> heights) {
  stack<int> stack;
  int max_area = 0;
  for (int i = 0; i <= heights.size(); i++) {
    while (!stack.empty() && (i == heights.size() || heights[i] < heights[stack.top()])) {
      int height = heights[stack.top()];
      stack.pop();
      max_area = std::max(max_area, height * (stack.empty() ? i : i - stack.top() - 1));
    }
    stack.emplace(i);
  }
  return max_area;
}

int MaxRectSubmatrixClean(const vector<vector<int> >& A) {
  vector<int> table(A.front().size());
  int max_rect_area = 0;
  for (int i = A.size(); i >= 0; i--) {
    for (int j = 0; j < A[i].size(); j++) {
      table[j] = A[i][j] ? i + 1 < A.size() ? table[j] + 1 : 1 : 0;
    }
    max_rect_area = std::max(max_rect_area, CalculateLargestRectangleClean(table));
  }
  return max_rect_area;
}

int main(int argc, char** argv) {   

  vector<vector<int> > A{{6, -5, -7, 4, -4}, 
                        {-9, 3, -5, 6, 2},
                        {-10, 4, 7, -6, 3},
                        {-8, 9, -3, 3, -7}};

  vector<vector<int> > B{{0, 1, 1, 1, 0}, 
                         {1, 0, 1, 1, 0},
                         {0, 1, 1, 1, 1},
                         {1, 0, 0, 1, 0}};

  vector<int> buildings{3, 3, 3, 4, 4, 4, 4, 4, 3, 6, 6, 6, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1};
 
  cout << CalculateLargestRectangle(buildings) << endl;
  cout << Max2DSubarraySumBookSol1(B) << endl;
  cout << MaxRectSubmatrixClean(B) << endl;

  cout << MaxSquareSubmatrix(B) << endl;

  return 0; 
}


