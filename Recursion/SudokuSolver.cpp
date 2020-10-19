/*
* SudokuSolver.cpp
* -----------------
*
* Chapter 16 Question 9
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

const int kEmptyEntry = 0;

bool isValidCandidate(vector<vector<int> >& partial_assignment, int row, int col, int val) {

  //check row validity
  for (int i = 0; i < 9; i++) {
    if (partial_assignment[row][i] == val) {
      return false;
    }
  }

  //check column validity
  for (int i = 0; i < 9; i++) {
    if (partial_assignment[i][col] == val) {
      return false;
    }
  }

  //check region constraints
  int region_row = row / 3;
  int region_col = col / 3;
  // for (int i = region_row * 3; i < region_row * 3 + 3; ++i) {
  //   for (int j = region_col * 3; i < region_col * 3 + 3; ++j) {
  //     if ((i != row && j != col) && partial_assignment[i][j] == candidate) {
  //       return false;
  //     }
  //   }
  // }

  int region_size = sqrt(partial_assignment.size());
  int I = row / region_size;
  int J = col / region_size;
  for (int a = 0; a < region_size; a++) {
    for (int b = 0; b < region_size; b++) {
      if (partial_assignment[I * region_size + a][J * region_size + b] == val) {
        return false;
      }
    }
  }

  return true;
}

bool SolveSudokuHelper(vector<vector<int> >& partial_assignment, int row, int col) {
  int size = partial_assignment.size();
  
  if (col == size) {
    row++;
    col = 0;
  }

  if (row == size) {
    return true; //entire matrix has been filled without conflict
  }

  if (partial_assignment[row][col] != kEmptyEntry) {
    return SolveSudokuHelper(partial_assignment, row, col + 1);
  }

  for (int i = 1; i <= partial_assignment.size(); ++i) {
    if (isValidCandidate(partial_assignment, row, col, i)) {
      partial_assignment[row][col] = i;

      if (SolveSudokuHelper(partial_assignment, row, col + 1)) {
        return true;
      }
    }
  }

  // for (int i = row; i <= size; ++i) {
  //   for (int j = col; j < size; ++j) {
  //     //cout << "ROW: " << row << " - COL: " << col << " Prev VAL: " << partial_assignment[row][col] << endl;

  //     if (partial_assignment[row][col] != 0) { continue; }
      
  //     for (int k = 1; k <= 9; ++k) {

  //       if (isValidCandidate(partial_assignment, row, col, k)) {
  //         partial_assignment[row][col] = k;
  //         if (SolveSudokuHelper(partial_assignment, row, col + 1)){
  //           return true;
  //         };
  //       }
  //     }

  //   }
  // }
  
  partial_assignment[row][col] = kEmptyEntry; //undo assignment

  
  return false;
}

bool SolveSudoku(vector<vector<int> >& partial_assignment) {
  return SolveSudokuHelper(partial_assignment, 0, 0);
}


int main(int argc, char* argv[]) {
  vector<vector<int>> A(9, vector<int>(9, 0));
  A[0] = {0, 2, 6, 0, 0, 0, 8, 1, 0};
  A[1] = {3, 0, 0, 7, 0, 8, 0, 0, 6};
  A[2] = {4, 0, 0, 0, 5, 0, 0, 0, 7};
  A[3] = {0, 5, 0, 1, 0, 7, 0, 9, 0};
  A[4] = {0, 0, 3, 9, 0, 5, 1, 0, 0};
  A[5] = {0, 4, 0, 3, 0, 2, 0, 5, 0};
  A[6] = {1, 0, 0, 0, 3, 0, 0, 0, 2};
  A[7] = {5, 0, 0, 2, 0, 4, 0, 0, 9};
  A[8] = {0, 3, 8, 0, 0, 0, 4, 6, 0};
  
  SolveSudoku(A);
  assert(SolveSudoku(A));
  vector<vector<int>> golden_A{
      {7, 2, 6, 4, 9, 3, 8, 1, 5}, {3, 1, 5, 7, 2, 8, 9, 4, 6},
      {4, 8, 9, 6, 5, 1, 2, 3, 7}, {8, 5, 2, 1, 4, 7, 6, 9, 3},
      {6, 7, 3, 9, 8, 5, 1, 2, 4}, {9, 4, 1, 3, 6, 2, 7, 5, 8},
      {1, 9, 4, 8, 3, 6, 5, 7, 2}, {5, 6, 7, 2, 1, 4, 3, 8, 9},
      {2, 3, 8, 5, 7, 9, 4, 6, 1}};
  
  // for (size_t i = 0; i < 9; ++i) {
  //   for (size_t j = 0; j < 9; ++j) {
  //     cout << i << " " << j << endl;
  //     assert(A[i][j] == golden_A[i][j]);
  //   }
  // }
  return 0;
}
