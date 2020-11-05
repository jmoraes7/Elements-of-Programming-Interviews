/*
* DetermineCriticalHeight.cpp
* -----------------
*
* Chapter 22 Question 39
*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;

using std::default_random_engine;
using std::endl;
using std::get;
using std::hash;
using std::numeric_limits;
using std::ostream;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

int GetMaxNumberDrops(int floors, int eggs) {
  cout << "EGGS: " << eggs << " FLOORS: " << floors << endl;
  vector<vector<int> > dp(floors + 1, vector<int>(eggs + 1, 0));

  //fill out cases where we have 1 egg
  for (int i = 1; i < dp.size(); i++) {
    dp[i][1] = i;
  }

  //fill out cases where we're at floor 1
  for (int i = 1; i < dp[0].size(); i++) {
    dp[1][i] = 1;
  }

  for (int i = 2; i < dp.size(); i++) {
    for (int j = 2; j < dp[0].size(); j++) {
      dp[i][j] = std::numeric_limits<int>::max();
      for (int x = 1; x <= i; x++) {
        int egg_breaks = dp[i - x][j];
        int egg_survives = dp[x-1][j-1];

        dp[i][j] = std::min(dp[i][j], std::max(egg_breaks, egg_survives) + 1);
      }


    }
  }

  for (vector<int> x : dp ) {
    for (int y : x) {
      cout << y << " ";
    }
    cout << endl;
  }
  return dp[floors][eggs];
} 


int GetMaxFeasbleHeightHelper(int tries, int eggs, vector<vector<int> >* DP) {
  if (tries == 0 || eggs == 0) {
    return 0;
  } else if (eggs == 1) {
    return tries;
  } 

  if ((*DP)[tries][eggs] == -1) {
    (*DP)[tries][eggs] = GetMaxFeasbleHeightHelper(tries - 1, eggs - 1, DP)
                        + GetMaxFeasbleHeightHelper(tries - 1, eggs, DP)
                        + 1;
  }

  return (*DP)[tries][eggs];
}

int GetMaxFeasibleHeight(int tries, int eggs) {
  vector<vector<int> > DP(tries + 1, vector<int>(eggs + 1, -1));
  return GetMaxFeasbleHeightHelper(tries, eggs, &DP);
}

int main(int argc, char** argv) {   

  //int eggs = 1, floors = 10;
  int eggs = 4, floors = 8;

  cout << GetMaxNumberDrops(floors, eggs) << endl;

  int tries = 11;
  eggs = 8;

  cout << GetMaxFeasibleHeight(tries, eggs) << endl;

  return 0; 
}


