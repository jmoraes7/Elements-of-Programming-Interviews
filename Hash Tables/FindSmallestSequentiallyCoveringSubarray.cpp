/*
* FindSmallestSequentiallyCoveringSubarray.cpp
* -----------------
*
* Chapter 13 Question 9
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::istringstream;
using std::list;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

std::pair<int, int> FindSequentiallyCoveringSubarray(const vector<string>& paragraph,
                                      const vector<string>& keywords) {

  unordered_map<string, int> keyword_to_idx;
  for (int i = 0; i < keywords.size(); i++) {
    keyword_to_idx[keywords[i]] = i;
  }

  int int_max = std::numeric_limits<int>::max();
  std::pair<int, int> res = {-1, -1};

  vector<int> most_recent_occurence(keywords.size(), -1);
  vector<int> shortest_subarray_length(keywords.size(), int_max);

  int shortest_distance = int_max;
  for (int i = 0; i < paragraph.size(); i++) {

    auto it = keyword_to_idx.find(paragraph[i]);
    if (it != keyword_to_idx.end()) { 
      int idx = it->second;
      cout << paragraph[i] << " " << idx << endl;
      //if elem is part of valid subarray
      if (idx == 0) {
        shortest_subarray_length[idx] = 1;
      } else if (shortest_subarray_length[idx - 1] != int_max) {
        int dist_to_prev_keyword = i - most_recent_occurence[idx - 1];

        shortest_subarray_length[idx] = 
                  dist_to_prev_keyword + shortest_subarray_length[idx - 1];
      }

      most_recent_occurence[idx] = i;

      if (idx == keywords.size() - 1 && shortest_subarray_length.back() < shortest_distance) {
            shortest_distance = shortest_subarray_length.back();
            res = {i - shortest_subarray_length.back() + 1, i};
      }         
    } 
  }

  return res;
}

int main(int argc, char** argv) {    
  vector<string> A{"a", "b", "c", "b", "a", "d", "c",
                    "a", "e", "a", "a", "b", "e"};

  vector<string> keywords{"b", "c", "e"};

  std::pair<int, int> result = FindSequentiallyCoveringSubarray(A, keywords);
  
  cout << result.first << " " << result.second << endl;

  return 0;
}
