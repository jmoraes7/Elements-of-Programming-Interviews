/*
* GeneratePascalTriangle.cpp
* -----------------
*
* Chapter 6 Question 20
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

vector<vector<int> > GeneratePascalTriangle(int num_rows) {
  vector<vector<int> > triangle;

  for (int i = 0; i < num_rows; ++i) {
    triangle.push_back(vector<int>());
    
    for (int j = 0; j <= i; ++j) {
      if (j == 0 || j == i ) {
        triangle[i].push_back(1);
      }
      
      else {
        int num1 = triangle[i-1][j-1];
        int num2 = triangle[i-1][j];
        cout << "HELLO - " << num1 << " " << num2 << " (" << i << ", " << j << ") " << endl;
        triangle[i].push_back(num1 + num2);
      } 
    }
  }
  

  // cout<< endl << "TRIANGLE SIZE: " << triangle.size() << " " << triangle[0].size() << endl;;
  // for (int x : triangle[0]) {
  //   cout << x << " ";
  // }
  // cout << endl;

  // for (int x : triangle[1]) {
  //   cout << x << " ";
  // }
  // cout << endl;

  // for (int x : triangle[2]) {
  //   cout << x << " ";
  // }
  // cout << endl;

  // for (int x : triangle[3]) {
  //   cout << x << " ";
  // }
  // cout << endl;
  
  // cout << triangle[1][1] << endl;
  
  for (int i = 0; i < triangle.size(); i++) {
    for (int x : triangle[i]) {
      cout << x << " ";
    }
    cout << endl;
  }
  cout << endl;

  return triangle;
}

int main()
{     

  vector<vector<int> > vals = GeneratePascalTriangle(6);
  
  // for (int i = 0; i < vals.size(); i++) {
  //   for (int j = 0; j < vals[0].size(); ++j) {
  //     cout << vals[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;
    return 0;
}