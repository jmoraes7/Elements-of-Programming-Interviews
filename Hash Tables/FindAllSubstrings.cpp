/*
* FindAllSubstrings.cpp
* -----------------
*
* Chapter 13 Question 13
*/

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
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
using std::greater;
using std::ifstream;
using std::istringstream;
using std::list;
using std::ofstream;
using std::priority_queue;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

bool MatchAllWordsInDict(const string& s, unordered_map<string, int> dict, 
                          size_t start, size_t num_words, size_t unit_size) {
  
  unordered_map<string, int> count_dict;
  for (size_t i = 0; i < num_words; i++) {

    string word = s.substr(start + i*unit_size, unit_size);

    if (dict.find(word) == dict.end()) {
      return false;
    } else {
      if (count_dict.find(word) != count_dict.end()) { //word already in substr
        return false;
      }
      count_dict[word]++;
    }
  }

  return true;
}
 
vector<int> FindAllSubstrings(const string& s, const vector<string>& words) {
  unordered_map<string, int> dict;
  for (const string& word : words) {
    ++dict[word];
  }

  auto unit_size = words.front().size();
  vector<int> result;
  for (size_t i = 0; i + unit_size * words.size() <= s.size(); ++i) {
    if (MatchAllWordsInDict(s, dict, i, words.size(), unit_size)) {
      result.push_back(i);
    }
  }

  return result;
}

int main(int argc, char** argv) {    
  string s = "amanaplanacanal";
  vector<string> words{"can", "apl", "ana"};

  vector<int> result = FindAllSubstrings(s, words);

  for (int x : result) {
    cout << x << endl;
  }
  return 0;
}
