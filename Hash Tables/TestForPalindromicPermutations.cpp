/*
* TestForPalindromicPermutations.cpp
* -----------------
*
* Chapter 13 Question 2
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

bool CanStringBePalindrome(string s) {

  unordered_map<char, int> char_freq_table;

  for (int i = 0; i < s.size(); i++) {
    char c = s[i];
    if (char_freq_table.find(c) != char_freq_table.end()) {
      char_freq_table.erase(c);
    } else {
      char_freq_table[c] = 1;
    }
  }

  return char_freq_table.size() < 2;
}

int main(int argc, char** argv) {  
  string s = "abba";
  
  cout << CanStringBePalindrome(s) << endl;
  return 0;
}
