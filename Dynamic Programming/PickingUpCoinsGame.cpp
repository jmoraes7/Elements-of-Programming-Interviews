/*
* PickingUpCoinsGame.cpp
* -----------------
*
* Chapter 17 Question 10
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

int PickUpCoinsHelper(const vector<int>& C, int start, int end, vector<vector<int> >* T) {

  if (start > end) {
    return 0;
  }


  if ((*T)[start][end] == -1) {
    (*T)[start][end] = std::max(C[start] + std::min(PickUpCoinsHelper(C, start + 2, end, T),
                                                    PickUpCoinsHelper(C, start + 1, end - 1, T)),
                                C[end] + std::min(PickUpCoinsHelper(C, start, end - 2, T),
                                                  PickUpCoinsHelper(C, start + 1, end - 1, T)));

    

  }

  return (*T)[start][end];
}

int PickUpCoins(const vector<int>& C) {
  vector<vector<int> > T(C.size(), vector<int>(C.size(), -1));

  return PickUpCoinsHelper(C, 0, C.size() - 1, &T);
}

int main(int argc, char** argv) {   
  
  vector<int> coins = {25, 5,  10, 5,  10, 5,  10, 25,
                       1,  25, 1,  25, 1,  25, 5,  10};

  cout << PickUpCoins(coins);

  return 0;
}

