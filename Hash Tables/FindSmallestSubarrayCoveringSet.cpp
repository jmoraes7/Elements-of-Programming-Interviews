/*
* FindSmallestSubarrayCoveringSet.cpp
* -----------------
*
* Chapter 13 Question 8
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

std::pair<int, int> FindSmallestArrayCoveringSubset3(istringstream* sin, 
                                              const vector<string>& keywords) {
  
  list<int> loc;
  unordered_map<string, list<int>::iterator > dict;
  for (string s : keywords) {
    dict[s] = loc.end();
  }

  int max_int = std::numeric_limits<int>::max();
  std::pair<int, int> result{0, max_int};

  int idx = 0;
  string s;
  while(*sin >> s) {
    auto it = dict.find(s);
    if (it != dict.end()) {

      if (it->second != loc.end()) { //if keyword has been seen before
        loc.erase(it->second);
      }      
      
      loc.push_back(idx);
      it->second = --loc.end();


      if (loc.size() == keywords.size()) {
        if (idx - loc.front() < result.second - result.first ) {
          result = {loc.front(), idx};
        }
      }
    }

    idx++;
  }

  return result;
}
std::pair<int, int> FindSmallestArrayCoveringSubset2(const vector<string>& paragraph, 
                                              const unordered_set<string>& keywords) {
  
  int max_int = std::numeric_limits<int>::max();
  unordered_map<string, int> keywords_in_subarray;
  std::pair<int, int> result{0, max_int};

  int left = 0, right = 0;
  while (right < paragraph.size()) {
    
    while (right < paragraph.size() && keywords_in_subarray.size() != keywords.size()) {
      if (keywords.find(paragraph[right]) != keywords.end()) {
        keywords_in_subarray[paragraph[right]]++;
      }
      ++right;
    }

    while (left < right && keywords_in_subarray.size() == keywords.size()) {
      string word = paragraph[left];

      if (keywords.find(word) != keywords.end()) {
        --keywords_in_subarray[word];
        if (keywords_in_subarray.find(word)->second == 0){
          keywords_in_subarray.erase(word);
        }

        if ((right - left) < (result.second - result.first)) {
            result = {left, right - 1};
        }
      }
      left++;
    }
  }

  return result;
}

std::pair<int, int> FindSmallestArrayCoveringSubset(const vector<string>& paragraph, 
                                              const unordered_set<string>& keywords) {
  
  int max_int = std::numeric_limits<int>::max();
  unordered_map<string, int> word_idx;
  std::pair<int, int> result{0, max_int};

  int left =  0, right = 0;
  while (right < paragraph.size()) {
    string word = paragraph[right];
    auto it = keywords.find(word);
    if (it != keywords.end()) { //if keyword
      if (left == 0) { left = right; }

      auto idx_map_it = word_idx.find(word);
      if (idx_map_it != word_idx.end()) { //if keyword has been seen before

        if (idx_map_it->second == left) { // if leftmost keyword shift left pointer to next keyword 
          do {
            left++;
          } while (keywords.find(paragraph[left]) == keywords.end());
        } 
      }   

      word_idx[word] = right;

      //update result if subarray with all keywords has been found
      if (word_idx.size() == keywords.size()) {
        if ((right - left) < result.second - result.first) {
          result = {left, right};
        }
      }  
    } 
    right++;
  }

  return result;
}

int main(int argc, char** argv) {    
  vector<string> A{"a", "b", "c", "b", "a", "d", "c",
                    "a", "e", "a", "a", "b", "e"};

  unordered_set<string> dict{"b", "c", "e"};
  vector<string> keywords{"b", "c", "e"};
  
  string s = "";
  for (string str : A) {
    s += str + " ";
  }
  istringstream sin(s);

  std::pair<int, int> result = FindSmallestArrayCoveringSubset3(&sin, keywords);
  
  cout << result.first << " " << result.second << endl;

  return 0;
}
