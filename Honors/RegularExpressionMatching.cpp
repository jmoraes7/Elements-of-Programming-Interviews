/*
* RegularExpressionMatching.cpp
* -----------------
*
* Chapter 22 Question 32
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::equal;
using std::make_unique;
using std::map;
using std::string;
using std::unique_ptr;
using std::vector;
using std::unordered_set;

bool IsMatchHere(string regex, int r_offset, string word, int word_offset) {
  if (regex.size() == r_offset) return true;
  cout << regex.substr(r_offset) << " " << word.substr(word_offset) << endl;

  if (regex[r_offset] == '$' && word_offset == word.size()) return true; 

  if (r_offset < regex.size() - 1 && regex[r_offset + 1] == '*') {
    for (int i = word_offset; i < word.size(); i++) {
      if ((regex[r_offset] == '.' || regex[r_offset] == word[i]) && 
            IsMatchHere(regex, r_offset + 2, word, i)) {
              return true;
      }
    }

    //See '*' matches zero character in s[s_offset : s.size() - 1].
    return IsMatchHere(regex, r_offset + 2, word, word_offset); 
  }

  return word_offset < word.size() && 
          (regex[r_offset] == '.' || (regex[r_offset] == word[word_offset])) &&
          IsMatchHere(regex, r_offset + 1, word, word_offset + 1);
}

bool IsMatch(string regex, string word) {
  if (regex.front() == '^') return IsMatchHere(regex, 1, word, 0);
  
  for (int i = 0; i <= word.size(); i++) {
    if (IsMatchHere(regex, 0, word,  i)) {
      return true;
    }
  }

  return false;
}

bool IsMatchDP(string regex, string word) {
  vector<vector<bool> > T(word.size() + 1, vector<bool>(regex.size() + 1, false));
  T[0][0] = true;

  for (int i =  1; i < regex.size(); i++) {
    if (regex[i - 1] == '*') {
      T[0][i] = T[0][i - 2];
    }
  }

  for (int i = 1; i < T.size(); i++) {
    for (int j = 1; j < T[i].size(); j++) {
      
      if (word[i-1] == regex[j-1] || regex[j-1] == '.') {
        T[i][j] = T[i-1][j-1];
      } else if (regex[j - 1] == '*') {

        T[i][j] = T[i][j-2];
        
        if (regex[j-2] == word[i-1] || regex[j-2] == '.') {
          T[i][j] = T[i][j] || T[i-1][j];
        }
      } 
    }
  }

  return T[word.size()][regex.size()];
}

int main(int argc, char** argv) {   
  assert(IsMatch(".", "a"));
  assert(IsMatch("a", "a"));
  assert(!IsMatch("a", "b"));
  assert(IsMatch("a.9", "aW9"));
  assert(!IsMatch("a.9", "aW19"));
  assert(IsMatch("^a.9", "aW9"));
  assert(!IsMatch("^a.9", "baW19"));
  assert(IsMatch(".*", "a"));
  assert(IsMatch(".*", ""));
  assert(IsMatch("c*", "c"));
  assert(!IsMatch("aa*", "c"));
  assert(IsMatch("ca*", "c"));
  assert(IsMatch(".*", "asdsdsa"));
  assert(IsMatch("9$", "xxxxW19"));

  assert(IsMatch(".*a", "ba"));

  assert(IsMatch(".*a", "ba"));
  assert(IsMatch("^a.*9$", "axxxxW19"));

  assert(IsMatch("^a.*W19$", "axxxxW19"));
  assert(IsMatch(".*a.*W19", "axxxxW19123"));
  assert(!IsMatch(".*b.*W19", "axxxxW19123"));
  assert(IsMatch("n.*", "n"));
  assert(IsMatch("a*n.*", "an"));
  assert(IsMatch("a*n.*", "ana"));
  assert(IsMatch("a*n.*W19", "anaxxxxW19123"));
  assert(IsMatch(".*a*n.*W19", "asdaaadnanaxxxxW19123"));
  assert(IsMatch(".*.*.a*n.*W19", "asdaaadnanaxxxxW19123"));

  cout << endl << "Success" << endl;

  cout << boolalpha << IsMatchDP("a*n.*", "anab") << endl;

  return 0;
}


