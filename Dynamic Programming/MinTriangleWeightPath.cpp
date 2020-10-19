/*
* MinTriangleWeightPath.cpp
* -----------------
*
* Chapter 17 Question 9
*/

#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::hash;
using std::list;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::tuple;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

int FindMinWeightPath(vector<vector<int> >& triangle) {
  if (triangle.empty()) {
    return 0;
  }

  vector<int> prev_row = triangle[0];
  for (int i = 1; i < triangle.size(); i++) {

    vector<int> curr_row = triangle[i];
    curr_row.front() += prev_row.front();
    for (int j = 1; j < curr_row.size() - 1; j++) {
      curr_row[j] += std::min(prev_row[j-1], prev_row[j]);
    }
    curr_row.back() += prev_row.back();

    swap(curr_row, prev_row);
  }

  return *min_element(prev_row.begin(), prev_row.end());
}


int main(int argc, char** argv) {   
  
  vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}; 

  cout << FindMinWeightPath(triangle);

  return 0;
}

