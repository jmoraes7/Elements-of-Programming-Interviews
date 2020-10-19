/*
* HouseMajority.cpp
* -----------------
*
* Chapter 17 Question 12
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_real_distribution;
using std::vector;

double HouseMajorityHelper(const vector<double>& prob, int r, int n,
                            vector<vector<double> >& P) {
  
  if (r > n) {
    return 0.0;   // Base Case: not enough Republicans
  } else if (r == 0 && n == 0) {
    return 1.0; // Base Case
  } else if (r < 0) {
    return 0.0;
  }

  if (P[r][n] < 0) {
    
    P[r][n] = HouseMajorityHelper(prob, r-1, n-1, P) * prob[n-1] 
              + HouseMajorityHelper(prob, r, n-1, P) * (1 - prob[n-1]);
  }

  return P[r][n];
}

double HouseMajority(const vector<double>& prob, int n) {

  vector<vector<double> > P(n + 1, vector<double>(n+1, -1));

  double prob_sum = 0.0;
  for (int r = ceil(n / 2); r <= n; r++) {
    prob_sum += HouseMajorityHelper(prob, r, n, P);
  }

  return prob_sum;
}

void PrintVector(vector<double> prob) {
  sort(prob.begin(), prob.end());
  for (int i = 0; i < prob.size(); ++i) {
    cout << i << ":" << static_cast<int>(100 * prob[i])
         << (((i + 1) % 10 == 0) ? "\n" : "% ");
  }
  cout << endl;
}

int main(int argc, char** argv) {   
  default_random_engine gen((random_device())());
  int n = 435;
  vector<double> prob;
  prob.emplace_back(0.0);
  for (int i = 0; i < n; ++i) {
    uniform_real_distribution<double> dis(0, 1);
    prob.emplace_back(dis(gen));
  }
  PrintVector(prob);
  double ans = HouseMajority(prob, n);
  assert(0.0 <= ans && ans <= 1.0);
  cout << ans << endl;
  return 0;
}

