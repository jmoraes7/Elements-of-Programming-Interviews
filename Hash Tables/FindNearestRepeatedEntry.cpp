/*
* FindNearestRepeatedEntry.cpp
* -----------------
*
* Chapter 13 Question 7
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

#include "../Binary Trees/BinaryTreeNodeWithParent.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

string RandString(int len) {
  default_random_engine gen((random_device())());
  string ret = "";
  while (len--) {
    uniform_int_distribution<int> dis('a', 'z');
    ret += dis(gen);
  }
  return ret;
}

// O(n^2) checking
int CheckAnswer(const vector<string>& s) {
  int nearest_repeated_distance = numeric_limits<int>::max();
  for (int i = 0; i < s.size(); ++i) {
    for (int j = i + 1; j < s.size(); ++j) {
      if (s[i] == s[j]) {
        nearest_repeated_distance = min(nearest_repeated_distance, j - i);
      }
    }
  }
  return nearest_repeated_distance;
}

int FindNearestRepeatedEntry(vector<string>& paragraph) {
  unordered_map<string, int> char_most_recent_idx;
  int dist = std::numeric_limits<int>::max();

  for (int i = 0; i < paragraph.size(); ++i) {
    string word = paragraph[i];
    auto it = char_most_recent_idx.find(word);
    if (it != char_most_recent_idx.end()) {
      dist = std::min(dist, i - it->second);
    }
    char_most_recent_idx[word] = i;
  }

  return dist;
}

int main(int argc, char** argv) {  
  vector<string> A{"foo",    "bar",    "widget", "foo",
                      "widget", "widget", "adnan"};
  
  assert(CheckAnswer(A) == FindNearestRepeatedEntry(A));
  A = {"foo", "bar", "widget", "foo", "xyz", "widget", "bar", "adnan"};
  assert(CheckAnswer(A) == FindNearestRepeatedEntry(A));
  A = {"foo", "bar", "widget", "adnan"};
  assert(CheckAnswer(A) == FindNearestRepeatedEntry(A));
  A = {};
  assert(CheckAnswer(A) == FindNearestRepeatedEntry(A));
  A = {"foo", "foo", "foo"};
  assert(CheckAnswer(A) == FindNearestRepeatedEntry(A));
  default_random_engine gen((random_device())());
  for (int times = 0; times < 10; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    vector<string> s;
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(1, 10);
      s.push_back(RandString(dis(gen)));
    }
    assert(CheckAnswer(s) == FindNearestRepeatedEntry(s));
  }

  

  return 0;
}
