/*
* FindSequence2DArray.cpp
* -----------------
*
* Chapter 17 Question 5
*/
#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::hash;
using std::numeric_limits;
using std::random_device;
using std::tuple;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

struct FunctionCallParameters {
  int i, j, len;

  bool operator==(const FunctionCallParameters& p) const
  { 
      return i == p.i && j == p.j && len == p.len;  
  } 
};

struct Hash {
  size_t operator()(const FunctionCallParameters& t) const {
    return hash<int>()(t.i) ^ hash<int>()(t.j) ^ hash<int>()(t.len);
  }
};

bool FindSequenceHelper(const vector<vector<int> >&A, const vector<int>& sequence, 
                        int i, int j, int len, unordered_set<FunctionCallParameters, Hash>* cache) {
  if (len == sequence.size()) {
    return true;
  }
  
  FunctionCallParameters params{i, j, len};
  if (i < 0 || i >= A.size() || j < 0 || j > A[i].size() ||
      cache->find(params) != cache->cend()) {
    return false;
  }

  if (A[i][j] != sequence[len]) {
    return false;
  }

  cache->insert(params);

  return FindSequenceHelper(A, sequence, i-1, j, len + 1, cache) ||
          FindSequenceHelper(A, sequence, i+1, j, len + 1, cache) ||
          FindSequenceHelper(A, sequence, i, j-1, len + 1, cache) ||
          FindSequenceHelper(A, sequence, i, j+1, len + 1, cache);
}

bool FindSequence(const vector<vector<int> >& A, const vector<int>& sequence) {  
  unordered_set<FunctionCallParameters, Hash> cache;

  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < A[i].size(); j++) {
      if (FindSequenceHelper(A, sequence, i, j, 0, &cache)) {
        return true;
      }
    }
  }

  return false;
}

int main(int argc, char** argv) {   
  
  int n = 3, m = 3;
  vector<vector<int> > A{{1, 2, 3},
                         {3, 4, 5},
                         {5, 6, 7}};

  vector<int> s1 = {1, 3, 4, 6};
  vector<int> s2 = {1, 2, 3, 4};


  // unordered_set<FunctionCallParameters, Hash> t;
  // FunctionCallParameters test = {1, 2, 3};
  // FunctionCallParameters test2 = {1, 2, 3};


  cout << FindSequence(A, s1) << endl;

  return 0;
}

