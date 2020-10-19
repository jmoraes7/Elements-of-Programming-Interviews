/*
* MatrixInSpiralOrder.cpp
* -----------------
*
* Chapter 6 Question 18
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

using std::default_random_engine;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

vector<int> getMatrixInSpiralOrder(const vector<vector<int> > &square_matrix) {

  int offset = 0;
  int length = square_matrix.size();

  //x*x is faster than pow(x, 2)
  vector<int> result;

  while (offset <= square_matrix.size() / 2 ) {
    int row = offset, col = offset;

    //arrived at center element
    if (length % 2 != 0 && offset == square_matrix.size() - offset - 1) {
      result.push_back(square_matrix[row][col]);
      break;
    }

    //spiral right
    while (col < length - offset - 1) {
      result.push_back(square_matrix[row][col]);
      cout << "RIGHT: (" << row << ", " << col << ") Terminating condition: " << length - offset - 1 << endl;
      col++;
    }

    //spiral down
    while (row < length - offset - 1) {
      result.push_back(square_matrix[row][col]);
      cout << "DOWN: (" << row << ", " << col << ") Terminating condition: " << length - offset - 1 << endl;
      row++;
    }

    //spiral left
    while (col > offset) {
      result.push_back(square_matrix[row][col]);
      cout << "LEFT: (" << row << ", " << col << ") Terminating condition: " << offset << endl;
      col--;
    }

    //spiral up
    while (row > offset) {
      result.push_back(square_matrix[row][col]);
      cout << "UP: (" << row << ", " << col << ") Terminating condition: " << offset << endl;
      row--;
    }

    offset++;
  }
  return result;
}

vector<int> getSpiral(int offset, const vector<vector<int> > &square_matrix) {
  vector<int> spiral_ordering;

  if (offset == square_matrix.size() - offset - 1) {
    spiral_ordering.push_back(square_matrix[offset][offset]);
    return spiral_ordering;
  }

  for (int col = offset; col < square_matrix.size() - offset - 1; ++col) {
    spiral_ordering.push_back(square_matrix[offset][col]);
  }

  for (int row = offset; row < square_matrix.size() - offset - 1; ++row) {
    spiral_ordering.push_back(square_matrix[row][square_matrix.size() - offset - 1]);
  }

  for (int col = square_matrix.size() - offset - 1; col > offset; --col) {
    spiral_ordering.push_back(square_matrix[square_matrix.size() - offset - 1][col]);
  }

  for (int row = square_matrix.size() - offset - 1; row > offset; --row) {
    spiral_ordering.push_back(square_matrix[row][offset]);
  }

  return spiral_ordering;
}

vector<int> MatrixInSpiralOrder(const vector<vector<int> > &square_matrix) {
  vector<int> spiral_ordering;
  for (int offset = 0; offset < ceil(0.5 * square_matrix.size()); ++offset) {
    vector<int> arr = getSpiral(offset, square_matrix);
    spiral_ordering.insert(spiral_ordering.end(), arr.begin(), arr.end()); 
  }
  return spiral_ordering;
}

vector<int> MatrixInSpiralOrderConcise(vector<vector<int> > &square_matrix) {
  vector<vector<int> > shift{{0, 1}, {1,0}, {0, -1}, {-1, 0}};
  vector<int> spiral_ordering;
  int dir = 0, x = 0, y = 0;
 
  for (int i = 0; i < square_matrix.size() * square_matrix.size(); ++i) {
    
    spiral_ordering.push_back(square_matrix[x][y]);
    square_matrix[x][y] = 0;

    int next_x = x + shift[dir][0], next_y = y + shift[dir][1];

    if (next_x < 0 || next_x >= square_matrix.size() || next_y < 0 ||
        next_y >= square_matrix.size() || square_matrix[next_x][next_y] == 0) {
          dir = (dir + 1) % 4;
          next_x = x + shift[dir][0], next_y = y + shift[dir][1];
    }

    x = next_x, y = next_y;
  }
  return spiral_ordering;
}

int main()
{     
    vector<vector<int> > vec{{ 1, 2, 3 }, 
                             { 8, 9, 4 }, 
                             { 7, 6, 5 } }; 

    vector<vector<int> > arr{{ 1, 2, 3, 4 }, 
                             { 12, 13, 14, 5 }, 
                             { 11, 16, 15, 6 },
                             { 10, 9, 8, 7 }};   

    vector<vector<int> > big{{ 1, 2, 3, 4, 5 }, 
                          { 16, 17, 18, 19, 6 }, 
                          { 15, 24, 25, 20, 7 },
                          { 14, 23, 22, 21, 8 },
                          { 13, 12, 11, 10, 9 }};                                                


    vector<int> vals = MatrixInSpiralOrderConcise(big);
    
    for (int x : vals) {
      cout << x << " ";
    }    
    cout << endl;
    return 0;
}