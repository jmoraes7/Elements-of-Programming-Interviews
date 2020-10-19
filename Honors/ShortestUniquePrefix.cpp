/*
* ShortestUniquePrefix.cpp
* -----------------
*
* Chapter 22 Question 23
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

class Trie {
  public: 
    bool Insert(const string& s) {
      auto *p = root_.get();

      for (const char& c : s) {
        if (p->leaves.find(c) == p->leaves.end()) {
          p->leaves[c] = make_unique<TrieNode>(TrieNode());
        } 
        p = p->leaves[c].get();
      }

      if (p->isEndOfWord) {
        return false;
      } 

      p->isEndOfWord = true;
      return true;
    }

    string GetShortestUniquePrefix(string query) {
      string unique_prefix = "";
      auto *curr = root_.get();
      for (const char& c : query) {
        if (curr->leaves.find(c) == curr->leaves.end()) {
          unique_prefix += c;
          return unique_prefix;
        }
        
        unique_prefix += c;
        curr = curr->leaves[c].get();
      }

      return "";
    }

  private:
    struct TrieNode {
      bool isEndOfWord = false;
      unordered_map<char, unique_ptr<TrieNode> > leaves; 
    };

    unique_ptr<TrieNode> root_ = make_unique<TrieNode>(TrieNode());
};

string FindShortestUniquePrefix(vector<string> dict, string s) {
  Trie trie;
  for (const string& s : dict) {
    trie.Insert(s);
  }
  
  return trie.GetShortestUniquePrefix(s);
}

int main(int argc, char** argv) {   
  vector <string> dict{"dog", "be", "cut", "car", "cat"};
  string query = "cat";
  

  cout << FindShortestUniquePrefix(dict, query) << endl;
  
  return 0;
}


