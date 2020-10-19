/*
* NQueens.cpp
* -----------------
*
* Chapter 16 Question 2
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

bool IsValid(const vector<int>& col_placement) {
  int row_id = col_placement.size() - 1;

  for (int i = 0; i < row_id; ++i) {
    int diff = abs(col_placement[i] - col_placement[row_id]);

    if (diff == 0 || diff == row_id - i) {
      return false;
    }
  }

  return true;
}

void SolveNQueens(int n, int row, vector<int>* col_placement,
                  vector<vector<int> >* result) {
  
  if (row == n) {
    result->push_back(*col_placement);
  } else {
    for (int col = 0; col < n; ++col) {
      col_placement->push_back(col);

      if (IsValid(*col_placement)) {
        SolveNQueens(n, row + 1, col_placement, result);
      }

      col_placement->pop_back();
    }
  }
}
vector<vector<int> > NQueens(int n) {
  vector<int> placement;
  vector<vector<int> > result; 

  SolveNQueens(n, 0, &placement, &result);

  return result;
}

vector<string> ToTextRepresentation(const vector<int>& col_placement) {
  vector<string> sol;
  for (int row : col_placement) {
    string line(col_placement.size(), '.');
    line[row] = 'Q';
    sol.push_back(line);
  }
  return sol;
}

static void SimpleTest() {
  auto result = NQueens(2);
  assert(0 == result.size());

  result = NQueens(3);
  assert(0 == result.size());

  result = NQueens(4);
  assert(2 == result.size());

  vector<int> place1 = {1, 3, 0, 2};
  vector<int> place2 = {2, 0, 3, 1};
  assert(result[0] == place1 || result[0] == place2);
  assert(result[1] == place1 || result[1] == place2);
  assert(result[0] != result[1]);
}

int main(int argc, char** argv) {
  SimpleTest();
  default_random_engine gen((random_device())());
  int n;
  if (argc == 2) {
    n = stoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 15);
    n = dis(gen);
  }
  cout << "n = " << n << endl;
  auto result = NQueens(n);
  for (const vector<int>& vec : result) {
    vector<string> text_rep = ToTextRepresentation(vec);
    for (const string& s : text_rep) {
      cout << s << endl;
    }
    cout << endl;
  }
  return 0;
}