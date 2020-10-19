/*
* SubstringSearch.cpp
* -----------------
*
* Chapter 7 Question 14
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

using std::default_random_engine;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

static int prime = 3;

int getHash(string s) {
  
  int hash = 0;
  for (int i = 0; i < s.size(); ++i) {
    hash += (int) s.at(i) * pow(prime, i);
  }
  
  return hash;
}

int rollHash(string s, int prev_hash, int curr_idx, int pattern_size) {
  if (curr_idx == 0) { 
    return getHash(s.substr(0, pattern_size));
  }

  int new_hash = (prev_hash - (int) s.at(curr_idx - 1)) / prime;

  new_hash += (int) s.at(curr_idx + pattern_size - 1) * pow(prime, pattern_size - 1);

  return new_hash;
}

int RabinKarp(const string& s, string pattern) {
  if (s.size() < pattern.size()) 
    return -1;

  int rolling_hash = 0;
  int pattern_hash = getHash(pattern);

  for (int i = 0; i <= s.size() - pattern.size(); ++i) {
    rolling_hash = rollHash(s, rolling_hash, i, pattern.size());

    if (rolling_hash == pattern_hash)
      return i;
  }

  return -1; 
}

vector<int> buildPrefixArray(string pattern) {
  vector<int> arr(pattern.size());

  int i = 1, j = 0;
  while (i < pattern.size()) {
    if (pattern.at(i) == pattern.at(j)) {
      arr[i] = ++j;
    } 
    
    else {
      while (pattern.at(i) != pattern.at(j) && j > 0) {
        j = arr[j-1];
      }

      arr[i] = j;

      if (pattern.at(i) == pattern.at(j)) { arr[i]++; }
    }

    i++;
  }

  return arr;
}

int KMP(const string& s, string pattern) {
  vector<int> prefix_array = buildPrefixArray(pattern);

  int count = 0;

  for (int i = 0; i < s.size(); ++i) {
    //cout << count << " ";
    
    if (s.at(i) == pattern.at(count)) {
      count++;
    }

    else if (count != 0) {
      count = prefix_array[count - 1];
      i--;
    }

    if (count == pattern.size()) {
      return i - pattern.size() + 1;
    }
  }
  // cout << endl;

  return -1;
}

int BoyerMoore(const string& s, string pattern) {


  return -1; 
}

int main()
{  
  string text = "abcxabcdabxabcdabcdabca";
  string pattern1 = "abcdabca";
  string pattern2 = "xabc";
  string pattern3 = "bac";

  int substring_idx = RabinKarp(text, pattern1);
  cout << "Rabin Karp Output: " << substring_idx << endl;

  // text = "abxabbcbabcaby";
  // string pattern = "abcaby";

  substring_idx = KMP(text, pattern1);
  cout << "KMP Output: " << substring_idx << endl;

  // cout << "Boyer Moore Karp Output: " << RabinKarp(text, pattern1) << endl;

  return 0;
}