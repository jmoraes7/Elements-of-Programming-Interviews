/*
* FillEnclosedRegions.cpp
* -----------------
*
* Chapter 19 Question 4
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

void MarkRegionIfSurrounded(size_t i, size_t j, vector<deque<bool> >* board,
                            vector<vector<bool> >* visited) {
  const array<array<int, 2>, 4> dir = {{
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
  }};

  vector<std::pair<size_t, size_t> > q; //use vector as queue
  q.emplace_back(i, j), (*visited)[i][j] = true;
  bool is_enclosed = true;
  int idx = 0;
  while (idx < q.size()) {
    const auto curr = q[idx++];
    
    if (curr.first == 0 || curr.first == board->size() - 1 || curr.second == 0 ||
        curr.second == (*board)[curr.first].size() - 1) {
      is_enclosed = false;
    } else {
      for (const auto& d : dir) {
        std::pair<size_t, size_t> next(curr.first + d[0], curr.second + d[1]);
        if ((*board)[next.first][next.second] == false && !(*visited)[next.first][next.second]) {
          q.emplace_back(next.first, next.second);
          (*visited)[next.first][next.second] = true;
        }
      }
    }
  }

  if (is_enclosed) {
    for (const auto& elem : q) {
      (*board)[elem.first][elem.second] = true;
    }
  }
}

void FillEnclosedRegions(vector<deque<bool> >* board) {
  if (board->empty()) {
    return;
  }

  vector<vector<bool> > visited(board->size(), vector<bool>(board->front().size(), false));
  for (size_t i = 1; i < board->size() - 1; i++) {
    for (size_t j = 1; j < (*board)[i].size() - 1; j++) {
      if ((*board)[i][j] == false && !visited[i][j]) {
        MarkRegionIfSurrounded(i, j, board, &visited);
      }
    }
  }
}

int main(int argc, char** argv) {   
  vector<deque<bool> > board{{true, true, true, true},
                            {false, true, false, true},
                            {true, false, true, true},
                            {true, true, true, true},};

  FillEnclosedRegions(&board);
  
  for (deque<bool> row : board) {
    for (bool elem : row) {
      cout << elem << " ";
    }
    cout << endl;
  }

  return 0;
}


