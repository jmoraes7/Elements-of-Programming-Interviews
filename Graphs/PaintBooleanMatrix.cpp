/*
* PaintBooleanMatrix.cpp
* -----------------
*
* Chapter 19 Question 3
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <utility>
#include <vector>

using std::array;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::random_device;
using std::stoul;
using std::uniform_int_distribution;
using std::vector;

void FlipColorDFS(int row, int col, vector<deque<bool> > *A) {
  const array<array<int, 2>, 4> shift = {{
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
  }};

  const bool color = (*A)[row][col];
  (*A)[row][col] = !(*A)[row][col];
  
  for (const auto& s : shift) {
    int next_x = row + s[0];
    int next_y = col + s[1];
    
    if (next_x >= 0 && next_x < A->size() && next_y >=0 &&
          next_y < (*A)[next_x].size() && (*A)[next_x][next_y] == color) {
      FlipColorDFS(next_x, next_y, A);
    }
  }
}

void FlipColor(int row, int col, vector<deque<bool> > *A) {
  const bool color = (*A)[row][col];
  const array<array<int, 2>, 4> shift = {{
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
  }};

  queue<std::pair<int, int> > q;
  q.emplace(std::pair<int, int>{row, col});
  while (!q.empty()) {
    std::pair<int, int> curr = q.front();
    for (const auto& s : shift) {
      std::pair<int, int> next = {curr.first + s[0], curr.second + s[1]};

      if (next.first >= 0 && next.first < A->size() && next.second >= 0 && 
          next.second < (*A)[next.first].size() && (*A)[next.first][next.second] == color) {
            (*A)[next.first][next.second] = !(*A)[next.first][next.second];
            q.emplace(next);
      } 
    }
    q.pop();
  }
}

int main(int argc, char** argv) {   
  vector<deque<bool> > maze{{true, true, true, false},
                            {true, true, false, true},
                            {false, true, true, false},
                            {true, false, true, false},};

  FlipColorDFS(1, 1, &maze);
  
  for (deque<bool> row : maze) {
    for (bool elem : row) {
      cout << elem << " ";
    }
    cout << endl;
  }

  return 0;
}


