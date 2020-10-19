/*
* Search2DSortedArray.cpp
* -----------------
*
* Chapter 12 Question 7
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
using std::numeric_limits;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

bool Search2DSortedArray(vector<vector<int> > A, int k) {
  int rows = 0, cols = A[0].size() - 1;

  while (rows < A.size() && cols >= 0 ) {
    if (A[rows][cols] == k) { return true; }

    if (A[rows][cols] > k) {
      cols--;
    } else {
      rows++;
    }
  }

  return false;
}

int main(int argc, char** argv) {
  vector<vector<int> > A{{-1, 2, 4, 4, 6}, {1, 5, 5, 9, 21}, {3, 6, 6, 9, 22},
                       {3, 6, 8, 10, 24}, {8, 10, 12, 13, 40}};


  cout << Search2DSortedArray(A, 21) << endl;

  return 0;
}
