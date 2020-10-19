/*
* SudokuCheckerProblem.cpp
* -----------------
*
* Chapter 6 Question 17
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random> 
#include <unordered_map>
#include <set>

using namespace std;

using std::default_random_engine;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

bool HasDuplicate(const vector<vector<int> > &partial_assignment, int row_begin, int row_end,
                    int col_begin, int col_end) {
  vector<int> nums(3);
  iota(nums.begin(), nums.end(), 1);
  set<int> valid_nums(nums.begin(), nums.end()); 
 
  for (int i = row_begin; i < row_end; ++i) {
    for (int j = col_begin; j < col_end; ++j) {
      int elem = partial_assignment[i][j];

      cout << "(" << i << ", " << j << ")";
      if (!valid_nums.count(elem)) {
            cout << "INCORRECT ELEMENT IN Position (" << i << ", " << j << "): " << elem << endl;
            return false;
      }
      valid_nums.erase(elem); 
    }
    cout << endl;
  }
  cout << endl;

  return true;
}
bool isValidSudoku(const vector<vector<int> > &partial_assignment) {

  //check rows
  for (int i = 0; i < partial_assignment.size(); ++i) {
    if (!HasDuplicate(partial_assignment, i, i+1, 0, partial_assignment[0].size())) 
      return false;
  }

  //check columns
  for (int i = 0; i < partial_assignment[0].size(); ++i) {
    if (!HasDuplicate(partial_assignment, 0, partial_assignment.size(), i, i+1))
      return false;
    break;
  }

  //check grids (partial_assignment needs to be 9x9 for this to work)
  int region_size = sqrt(partial_assignment.size());
  for (int i = 0; i < region_size; ++i) {
    for (int j = 0; j < region_size; ++j) {
      if (!HasDuplicate(partial_assignment, region_size * i, region_size * (i+1), 
            region_size * j, region_size*(j+1)))
        return false;
    }
  }

  return true;
}

int main()
{   
    vector<vector<int> > vec{ { 1, 2, 3 }, 
                              { 3, 1, 2 }, 
                              { 2, 3, 1 } }; 
  
    cout << endl << isValidSudoku(vec);

    return 0;
}