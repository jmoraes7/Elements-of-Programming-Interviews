/*
* GenerateABSqrt.cpp
* -----------------
*
* Chapter 15 Question 8
*/
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <memory>
#include <map>
#include <set>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::set;
using std::unique_ptr;

struct ABSqrt2 {
  ABSqrt2(int a, int b) : a(a), b(b), val(a + b * sqrt(2)) {}

  bool operator <(const ABSqrt2& that) const { return val < that.val; }

  int a, b;
  double val;
};

vector<ABSqrt2> GenerateFirstKABSqrt2(int k) {
  set<ABSqrt2> candidates;
  candidates.emplace(0, 0);

  vector<ABSqrt2> results;
  while (results.size() < k) {

    auto next_smallest = candidates.cbegin();
    results.push_back(*next_smallest);

    candidates.emplace(next_smallest->a + 1, next_smallest->b);
    candidates.emplace(next_smallest->a, next_smallest->b + 1);
    candidates.erase(next_smallest);
  }

  return results;
}

vector<ABSqrt2> GenerateFirstKABSqrt2Fast(int k) {
  vector<ABSqrt2> results;
  results.push_back(ABSqrt2(0, 0));

  int i = 0, j = 0;
  while (results.size() < k) {
    ABSqrt2 result_i_plus_1(results[i].a + 1, results[i].b);
    ABSqrt2 result_j_plus_sqrt2(results[j].a, results[j].b + 1);

    cout << "i: " << i << " " << result_i_plus_1.val << ", j: " << j << " " << result_j_plus_sqrt2.val << endl;
    if (result_i_plus_1 < result_j_plus_sqrt2) {
      results.push_back(result_i_plus_1);
      ++i;
    } else if (result_j_plus_sqrt2 < result_i_plus_1) {
      results.push_back(result_j_plus_sqrt2); 
      ++j;
    } else {
      results.push_back(result_i_plus_1);
      ++i, ++j;
    }
  }

  return results;
}

int main(int argc, char** argv) {    

  vector <ABSqrt2> result = GenerateFirstKABSqrt2Fast(7);
 
  for (ABSqrt2 num : result) {
    cout << num.val << endl;
  }

  return 0;
}
