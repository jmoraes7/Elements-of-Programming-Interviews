/*
* RookAttack.cpp
* -----------------
*
* Chapter 22 Question 7
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::array;
using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::random_device;
using std::stoul;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

void RookAttack(vector<vector<int> >* A_ptr) {
  auto& A = *A_ptr;
  size_t m = A.size(), n = A[0].size();
  bool has_first_row_zero = false;
  for (size_t j = 0; j < n; j++){
    if (A[0][j] == 0) {
      has_first_row_zero = true;
      break;
    }
  }

  bool has_first_column_zero = false;
  for (size_t i = 0; i < m; i++) {
    if (A[i][0] == 0) {
      has_first_column_zero = true;
      break;
    }
  }

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      if (A[i][j] == 0) {
        cout << "HERE" << endl;
        A[i][0] = A[0][j] = 0;
      }
    }
  }

  for (size_t i = 1; i < m; i++) {
    if (A[i][0] == 0) {
      for (int j = 0; j < n; j++) {
        A[i][j] = 0;
      }
    }
  }

  
  for (size_t j = 1; j < m; j++) {
    if (A[0][j] == 0) {
      for (int i = 0; i < n; i++) {
        A[i][j] = 0;
      }
    }
  }

  if (has_first_row_zero) {
    for (size_t j = 0; j < n; j++) {
      A[0][j] = 0;
    }
  }

  if (has_first_column_zero) {
    for (size_t i = 0; i < m; i++) {
      A[i][0] = 0;
    }
  }
}

int main(int argc, char** argv) {   
  
  vector<vector<int> > A{{1, 0, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1}, 
                        {1, 1, 1, 1, 1, 1, 1, 1}, 
                        {1, 1, 1, 1, 1, 0, 1, 1}, 
                        {1, 1, 1, 0, 1, 1, 1, 1}, 
                        {1, 1, 1, 1, 1, 1, 1, 1}, 
                        {0, 1, 1, 1, 1, 0, 1, 1}, 
                        {1, 1, 1, 1, 1, 1, 1, 1}};
  
  RookAttack(&A);

  for (vector<int> row: A) {
    for (int x : row) {
      cout << x << " ";
    }
    cout << endl;
  }

  return 0;
}


