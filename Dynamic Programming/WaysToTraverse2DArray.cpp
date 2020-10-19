/*
* WaysToTraverse2DArray.cpp
* -----------------
*
* Chapter 17 Question 3
*/
#include <algorithm>
#include <cassert>
#include <cmath> 
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::deque;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

int NumberOfWaysWithObstacles(int n, int m, const vector<deque<bool> >& B) {
  if (B[0][0]) {
    return 0;
  }

  vector<int> path_counts(m, 1);
  for (int i = 1; i < n; i++) {
    path_counts[0] = B[i-1][0] ? 0 : 1;

    for (int j = 1; j < m; j++) {
      int num_paths_from_above = B[i-1][j] ? 0 : path_counts[j];
      int num_paths_from_left = B[i][j-1] ? 0 : path_counts[j-1];

      path_counts[j] = num_paths_from_above + num_paths_from_left;
    }
  }

  return path_counts[m-1];
} 
int WaysToTraverse2DArray(int n, int m) {
  if (n < m) {
    swap(n, m); //reduce space usage
  }

  vector<int> path_counts(m, 1);
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      path_counts[j] += path_counts[j-1];
    }
  }

  return path_counts[m-1];
} 

int main(int argc, char** argv) {   
  //cout << WaysToTraverse2DArray(5, 5);
  
  default_random_engine gen((random_device())());

  int n = 3, m = 3;
  
  vector<deque<bool> > B(n, deque<bool>(m));
  B[1][0] = true;
  B[1][2] = true;



  // for (size_t i = 0; i < n; ++i) {
  //   for (size_t j = 0; j < m; ++j) {
  //     uniform_int_distribution<int> dis(0, 9);
  //     int x = dis(gen);
  //     B[i][j] = ((x < 2) ? 1 : 0);
  //   }
  // }
  
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      cout << B[i][j] << ' ';
    }
    cout << endl;
  }

  cout << NumberOfWaysWithObstacles(n, m, B) << endl;

  return 0;
}

