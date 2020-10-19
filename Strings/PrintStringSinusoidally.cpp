/*
* PrintStringSinusoidally.cpp
* -----------------
*
* Chapter 7 Question 11
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

void snakeString(string& s) {
  string result;

  for (int i = 1; i < s.size(); i += 4) {
    result += s[i];
  }

  for (int i = 0; i < s.size(); i += 2) {
    result += s[i];
  }

  for (int i = 3; i < s.size(); i += 4) {
    result += s[i];
  }

  cout << result;
}


int main()
{  
  string s = "Hello World!";

  snakeString(s);

  return 0;
}