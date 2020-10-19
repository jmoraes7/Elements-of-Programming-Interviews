/*
* GeneratePalindromicDecompositions.cpp
* -----------------
*
* Chapter 16 Question 7
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

bool IsPalindromeClean(string s) {
  for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
    if (s[i] != s[j]) {
      return false;
    }
  }
  
  return true;
}
bool IsPalindrome(string s) {

  for (int i = 0; i < s.size() / 2; ++i) {    
    if (s[i] != s[s.size() - 1 - i]) {
      return false;
    }
  }

  return true;
}

void DirectedPalindromePartitioning(string s, int curr_start, int curr_end, bool isPalindromePreceding,
                                    vector<string> candidates, vector<vector<string> >& results ) {
  if (curr_end == s.size()) {
    if (isPalindromePreceding) { results.push_back(candidates); }
    return;
  }

  string candidate = s.substr(curr_start, curr_end - curr_start + 1);

  if (IsPalindrome(candidate)) {
    candidates.push_back(candidate);
    DirectedPalindromePartitioning(s, curr_end + 1, curr_end + 1, true, candidates, results);
    candidates.pop_back();
  }

  DirectedPalindromePartitioning(s, curr_start, curr_end + 1, false, candidates, results);
}

/*
* Book Solution
*/


vector<vector<string> > PalindromePartitioning(string s) {
  vector<vector<string> > results;
  vector<string> candidates;

  DirectedPalindromePartitioning(s, 0, 0, false, candidates, results);

  return results;
}




static void SimpleTest() {
  auto result = PalindromePartitioning("abbbac");
  vector<string> v0{"a", "b", "b", "b", "a", "c"};
  vector<string> v1{"a", "b", "bb", "a", "c"};
  vector<string> v2{"a", "bb", "b", "a", "c"};
  vector<string> v3{"a", "bbb", "a", "c"};
  vector<string> v4{"abbba", "c"};
  vector<vector<string> > golden{v0, v1, v2, v3, v4};

  for (vector<string> A : result) {
    for (string x : A) {
      cout << x << " ";
    }
    cout << endl;
  }
  // assert(result == golden);
}

int main(int argc, char* argv[]) {
  SimpleTest();


  return 0;
}
