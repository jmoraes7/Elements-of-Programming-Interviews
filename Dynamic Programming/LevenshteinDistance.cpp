/*
* LevenshteinDistance.cpp
* -----------------
*
* Chapter 17 Question 2
*/
#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::string;
using std::vector;

int LevenshteinDistance(string A, string B) {

  vector<vector<int> > dist(A.size() + 1, vector<int>(B.size() + 1));

  //initialize 0th row 
  for (int i = 1; i <= B.size(); i++) {
    dist[0][i] = i;
  }
  
  //initialize 0th column
  for (int i = 1; i <= A.size(); i++) {
    dist[i][0] = i;
  }

  for (int i = 1; i <= A.size(); i++) {
    for (int j = 1; j <= B.size(); j++) {

      if (A.at(i-1) != B.at(j-1)) {
        int curr_dist = std::min(std::min(dist[i][j-1], dist[i-1][j]), dist[i-1][j-1]);
        dist[i][j] = curr_dist + 1;
      } else {
        dist[i][j] = dist[i-1][j-1];
      }
    }
  }

  return dist[A.size()][B.size()];
}

int LevenshteinDistanceEfficient(string A, string B) {
  if (A.size() < B.size()) {
    swap(A, B);
  }

  vector<int> dist(B.size() + 1);
  
  //Initialization
  iota(dist.begin(), dist.end(), 0);

  for (int i = 1; i <= A.size(); i++) {
    int pre_i_1_j_1 = dist[0];
    dist[0] = i;  

    for (int j = 1; j <= B.size(); j++) {
       
      int pre_i_1_j = dist[j];
      
      dist[j] = A.at(i-1) == B.at(j-1) ? pre_i_1_j_1 : 
                1 + std::min(pre_i_1_j_1, std::min(dist[j-1], dist[j])); //min([i-1][j-1], min([i][j-1], [i-1][j]))

      pre_i_1_j_1 = pre_i_1_j;
    }
  }

  return dist[B.size()];
}

int main(int argc, char** argv) {   
  string A, B;

  A = "k", B = "sitt";
  assert(4 == LevenshteinDistanceEfficient(A, B));
  A = "Saturday", B = "Sunday";
  assert(3 == LevenshteinDistanceEfficient(A, B));
  A = "kitten", B = "sitting";
  assert(3 == LevenshteinDistanceEfficient(A, B));

  //cout << LevenshteinDistance(A, B) << endl;
  
  return 0;
}

