/*
* GasUpProblem.cpp
* -----------------
*
* Chapter 18 Question 7
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

const int kMPG = 1;

int FindStartCity(const vector<int>& G, const vector<int>& D) {
  int carry = 0;
  std::pair<int, int> city_carry_pair(0, 0);
  for (int i = 1; i < G.size(); i++) {
    cout << i << " " << carry << endl;
    carry += G[i - 1] - D[i-1];
    if (carry < city_carry_pair.second) {
      city_carry_pair = {i, carry};
    }
  }

  return city_carry_pair.first;
}

int main(int argc, char** argv) {   
  
  vector<int> gallons = {20, 15, 15, 15, 35, 25, 30, 15, 65, 45, 10, 45, 25};
  vector<int> distances = {15 * kMPG, 20 * kMPG, 50 * kMPG, 15 * kMPG,
                           15 * kMPG, 30 * kMPG, 20 * kMPG, 55 * kMPG,
                           20 * kMPG, 50 * kMPG, 10 * kMPG, 15 * kMPG,
                           15 * kMPG};

  int ans = FindStartCity(gallons, distances);

  cout << ans << endl;

  return 0;
}


