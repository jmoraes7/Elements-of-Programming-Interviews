/*
* HeavyHitterProblem.cpp
* -----------------
*
* Chapter 22 Question 45
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::greater;
using std::hash;
using std::istringstream;
using std::length_error;
using std::make_unique;
using std::unique_ptr;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::stoi; 
using std::unordered_map;
using std::unordered_set;
using std::vector;

vector<string> SearchFrequentItems(int k, istringstream* sin) {
  string buf;
  unordered_map<string, int> hash;
  int n = 0;

  while (*sin >> buf) {
    ++hash[buf], ++n;
    if (hash.size() == k) {
      auto it = hash.begin();
      while (it != hash.end()) {
        cout << it->first << " " << it->second << endl;

        (it->second)--;
        if (it->second == 0) {
          hash.erase(it++);
          
        } else {
          it++;
        }
      }
    }
  } 
  for (auto &it : hash) {
    it.second = 0;
  }

  
  sin->clear();
  sin->seekg(0, std::ios::beg);

  while (*sin >> buf) {
    if (hash.find(buf) != hash.end()) {
      ++hash[buf];
    }  
  }

  vector<string> res;
  for (auto &it : hash) {
    if (it.second > static_cast<double>(n) / k) {
      res.emplace_back(it.first);
    }
  }
  
  return res;
}

int main(int argc, char** argv) {   

  vector<string> arr{"e", "test", "test", "e", "abc", "test", "q", "e"};

  string str = "";
  for (string x : arr) {
    str += x;
    str += " ";
  }

  istringstream s(str);
  //str = "";
  
  int k = 4;
  vector<string> res = SearchFrequentItems(k, &s);

  cout << endl << "Results:" << endl;
  for (string x : res) {
    cout << x << endl;
  }

  return 0;
}


