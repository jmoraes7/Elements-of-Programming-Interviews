/*
* WordBreaking.cpp
* -----------------
*
* Chapter 17 Question 8
*/

#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::hash;
using std::list;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::tuple;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

vector<string> WordBreaking(string& s, unordered_set<string>& dict) {

  vector<int> T(s.size());

  for (int i = 0; i < s.size(); i++) {

    if (dict.count(s.substr(0, i + 1))) {
      T[i] = i + 1;
    }

    for (int j = 0; j < i && T[i] == 0; j++) {
      if (T[j] > 0 && dict.count(s.substr(j + 1, i - j))) {
        T[i] = i - j;
      }
    }
  }

  vector<string> result;

  if (T.back()) {
    int idx = s.size() - 1;
    while (idx > 0) {
      int str_len = T[idx];
      
      string substring = s.substr(idx - str_len + 1, str_len);
      
      result.insert(result.begin(), substring); //insert at beginning of vector since we're looping from back

      idx -= str_len;
    }
  }

  return result;
}



int main(int argc, char** argv) {   
  
  string t = "bed";
  string s = "bedbathandbeyond";
  unordered_set<string> dict = {"be", "bed", "bath", "and", "beyond", "hand"};
  
  auto result = WordBreaking(s, dict);


  for (string word : result) {
    cout << word << " ";
  }

  return 0;
}

