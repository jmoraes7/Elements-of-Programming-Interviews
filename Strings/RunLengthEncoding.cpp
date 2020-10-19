/*
* RunLengthEncoding.cpp
* -----------------
*
* Chapter 7 Question 12
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

string encode(string s) {
  string res;
  char curr = s.front();
  int count = 0; 

  for (int i = 0; i < s.size(); ++i) {
    if (s[i] != curr) {
      res += to_string(count) + curr;
      curr = s[i];
      count = 0;
    }
    count++;
  }

  res += to_string(count) + curr;

  return res;
}

string decode(string s) {
  string res;
  for (int i = 0; i < s.size(); i += 2) {
    int count = s[i] - '0';
    res.append(count, s[i+1]);
  }
  
  return res;
}

int main()
{  
  string encoded = "4a1b3c2a";
  string decoded = "aaaabcccaa";

  cout << "ENCODE: " << encode(decoded) << endl;
  cout << "DECODE: " << decode(encoded) << endl;

  return 0;
}