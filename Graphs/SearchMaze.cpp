/*
* SearchMaze.cpp
* -----------------
*
* Chapter 19 Question 2
*/

#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <random>
#include <vector>

using std::array;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::max;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

struct Coordinate {
  bool operator==(const Coordinate& that) const {
    return x == that.x && y == that.y;
  }
  
  int x, y;
};

bool isFeasible(const Coordinate& curr, vector<vector<bool> >& maze) {
  if (curr.x >= 0 && curr.x < maze.size() && curr.y >= 0 && 
        curr.y < maze[curr.x].size() && maze[curr.x][curr.y] == true) {
          return true;
  }
  return false;
}

bool SearchMazeHelper(const Coordinate& curr, const Coordinate& end, 
                      vector<vector<bool> >* maze, vector<Coordinate>* path) {
  
  if (curr == end) {
    return true;
  }

  const array<array<int, 2>, 4> shift = {
    {{1, 0}, {0, 1}, {0, -1}, {-1, 0}}
  };

  for (const auto& s : shift) {
    
    Coordinate candidate{curr.x + s[0], curr.y + s[1]};
    if (isFeasible(candidate, *maze)) {
      path->push_back(candidate);
      (*maze)[curr.x + s[0]][curr.y +s[1]] = false;
      if (SearchMazeHelper(candidate, end, maze, path)) {
        return true;
      }

      path->pop_back(); //leave maze coordinate as false in maze since we already know that it doens't lead to the end of the maze
    }
  }
  
  return false;
}

vector<Coordinate> SearchMaze(vector<vector<bool> > maze, const Coordinate& start, const Coordinate& end) {
  vector<Coordinate> path;
  maze[start.x][start.y] = false;
  path.push_back(start);
  if (!SearchMazeHelper(start, end, &maze, &path)) {
    path.pop_back();
  }
 
  return path;
}

int main(int argc, char** argv) {   
  vector<vector<bool> > maze{{false, true, true, true, true, true, false, false, true, true},
                           {true, true, false, true, true, true, true, true, true, true},
                           {false, true, false, true, true, false, false, true, false, false},
                           {true, true, true, false, false, false, true, true, false, true},
                           {true, false, false, true, true, true, true, true, true, true},
                           {true, false, false, true, true, false, true, false, false, true},
                           {true, true, true, true, false, true, true, true, true, true},
                           {false, true, false, true, false, true, false, true, true, true},
                           {false, true, false, false, true, true, true, false, false, false},
                           {true, true, true, true, true, true, true, false, false, true}};

  
  Coordinate start{9, 0};
  Coordinate end{0, 9};
  
  auto path = SearchMaze(maze, start, end);

  for (Coordinate c : path) {
    cout << "Row: " << c.x << " Col: " << c.y << endl;
  }

  return 0;
}


