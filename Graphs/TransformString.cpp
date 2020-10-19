/*
* TransformString.cpp
* -----------------
*
* Chapter 19 Question 8
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::array;
using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::random_device;
using std::stoul;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

struct SequenceCandidate {
  vector<string> prev;
};

vector<string> TransformString(string s, string t, unordered_set<string> dict) {
  SequenceCandidate sequence;
  SequenceCandidate start{{s}};
  queue<SequenceCandidate> q;
  q.emplace(start);
  while (!q.empty()) {
    
    SequenceCandidate c = q.front();
    string curr = c.prev.back();
    for (int i = 0; i < curr.size(); i++) {
      for (int j = 0; j < 26; j++) {
        string candidate = curr;
        candidate[i] = 'a' + j;

        if (dict.count(candidate)) {
          SequenceCandidate extended_candidate{c.prev};
          extended_candidate.prev.push_back(candidate);

          if (candidate == t) {
            return extended_candidate.prev;
          }

          dict.erase(candidate);
          q.emplace(extended_candidate);
        }
      }
    }

    q.pop();  
  }

  return {};
}

int main(int argc, char** argv) {   

  string s = "cat";
  string t = "dog";
  unordered_set<string>dict;
  dict.insert("bat");
  dict.insert("cot");
  dict.insert("dog");
  dict.insert("dag");
  dict.insert("dot");
  dict.insert("cat");

  auto sequence = TransformString(s, t, dict);

  for (string s : sequence) {
    cout << s << " ";
  }

  return 0;
}


