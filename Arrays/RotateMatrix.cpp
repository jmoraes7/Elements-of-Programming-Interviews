/*
* RotateMatrix.cpp
* -----------------
*
* Chapter 6 Question 19
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

vector<vector<int> > rotateMatrix(vector<vector<int> > &square_matrix) {

  int length = square_matrix.size() - 1;

  for (int offset = 0; offset < square_matrix.size() / 2; ++offset) { 
    for (int i = 0; i < length - (2*offset); ++i) {

      int temp = square_matrix[offset][offset + i];

      square_matrix[offset][offset + i] = square_matrix[length - offset-i][offset];
      square_matrix[length-offset-i][offset] = square_matrix[length - offset][length - offset - i];
      square_matrix[length - offset][length - offset - i] = square_matrix[offset + i][length - offset];
      square_matrix[offset + i][length - offset] = temp;
    }
  }

  return square_matrix;
}

int main()
{     
    vector<vector<int> > arr{{ 1, 2, 3 }, 
                             { 8, 9, 4 }, 
                             { 7, 6, 5 } }; 

    vector<vector<int> > vec{{ 1, 2, 3, 4 }, 
                             { 12, 13, 14, 5 }, 
                             { 11, 16, 15, 6 },
                             { 10, 9, 8, 7 }};   

    vector<vector<int> > big{{ 1, 2, 3, 4, 5 }, 
                          { 16, 17, 18, 19, 6 }, 
                          { 15, 24, 25, 20, 7 },
                          { 14, 23, 22, 21, 8 },
                          { 13, 12, 11, 10, 9 }};                                                

    for (int i = 0; i < big.size(); i++) {
      for (int j = 0; j < big[0].size(); ++j) {
        cout << big[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;

    vector<vector<int> > vals = rotateMatrix(big);
    

    for (int i = 0; i < vals.size(); i++) {
      for (int j = 0; j < vals[0].size(); ++j) {
        cout << vals[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
    return 0;
}