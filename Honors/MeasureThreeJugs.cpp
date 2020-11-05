/*
* MeasureThreeJugs.cpp
* -----------------
*
* Chapter 22 Question 37
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

struct Jug {
  int low, high;
};

class PairEqual { 
  public:
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
      return a.first == b.first && a.second == b.second;
    }
};

struct HashPair {
  size_t operator()(const std::pair<int, int>& p) const {
    return hash<int>()(p.first) ^ hash<int>()(p.second);
  }
};

bool CheckFeasibleHelper(const vector<Jug>& jugs, int L, int H, unordered_set<std::pair<int, int>, HashPair, PairEqual>* cache) {
  if (L > H || cache->find({L, H}) != cache->end() || (L < 0 && H < 0)) {
    return false;
  }

  for (const Jug& j : jugs) {
    if ((L <= j.low && j.high <= H) ||
      CheckFeasibleHelper(jugs, L - j.low, H - j.high, cache)) {
        return true;
      }
  }

  cache->emplace(L, H);
  return false;
}

bool CheckFeasible(const vector<Jug>& jugs, int L, int H) {
  unordered_set<std::pair<int, int>, HashPair, PairEqual> cache;
  return CheckFeasibleHelper(jugs, L, H, &cache);
}

int main(int argc, char** argv) {   
  
  vector<Jug> jugs = {{230, 240}, {290, 310}, {500, 515}};
  assert(CheckFeasible(jugs, 2100, 2300) == true);

  return 0;
}


