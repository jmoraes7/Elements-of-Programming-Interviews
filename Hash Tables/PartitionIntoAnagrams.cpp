/*
* PartitionIntoAnagrams.cpp
* -----------------
*
* Chapter 13 Question 1
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

vector<vector<string> > FindAnagrams(vector<string> dictionary) {

  unordered_map<string, vector<string> > sorted_string_to_anagrams;

  for (string s : dictionary) {
    string sorted_string(s);
    sort(sorted_string.begin(), sorted_string.end());
    sorted_string_to_anagrams[sorted_string].push_back(s);
  }

  vector<vector<string> > anagrams;
  for (auto p : sorted_string_to_anagrams) {
    anagrams.push_back(p.second);
  }

  return anagrams;
}

int main(int argc, char** argv) {  
  vector<string> dictionary{"debitcard", "elvis", "silent", "badcredit", "lives", "freedom", "listen", "levis"};

  auto anagram_groups = FindAnagrams(dictionary);

  for (auto group : anagram_groups) {

    for (string word : group) {
      cout << word << " ";
    }
    cout << endl << endl;

  }
  
  return 0;
}
