/*
* LookAndSayProblem.cpp
* -----------------
*
* Chapter 7 Question 8
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

string nextNumber(string s) {
  string ret = "";
  int count = 1;

  cout << s << endl;

  for (int i = 0; i < s.size(); ++i) {
    if (i == s.size() - 1 || s[i] != s[i+1]) {
      ret += to_string(count) + s[i];
      count = 1;
    }

    else { count++; }
  }
  
  //cout << "RET: " << ret << endl;
  return ret;
}

string LookAndSay(int n) {
  string s = "1";

  for (int i = 1; i < n; ++i) {
    s = nextNumber(s);    
  }

  return s;
}

int main()
{     
  string result = LookAndSay(7);

  cout << result << endl;

  return 0;
}