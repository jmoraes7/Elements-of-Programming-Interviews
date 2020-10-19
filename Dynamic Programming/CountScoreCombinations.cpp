/*
* CountScoreCombinations.cpp
* -----------------
*
* Chapter 17 Question 1
*/
#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::set;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

int CountCombinations(int k, const vector<int>& scores) {
  unordered_map<int, int> score_to_count;
  score_to_count[0]++;

  for (int score : scores) {
    for (int i = score; i <= k; i++) {
      if (score_to_count[i - score] > 0) {
        //cout << score << " " << i << endl;
        score_to_count[i] += score_to_count[i - score];
      }
    }
  }
  cout << score_to_count[6] << endl;
  return score_to_count[k];
}

void SimpleTest() {
  vector<int> scores = {2, 3, 7};
  cout << CountCombinations(12, scores) << endl;
  assert(4 == CountCombinations(12, scores));
  assert(1 == CountCombinations(5, scores));
  assert(3 == CountCombinations(9, scores));
}

int main(int argc, char** argv) {   

  SimpleTest();
  
  return 0;
}

