/*
* ReplaceAndRemove.cpp
* -----------------
*
* Chapter 7 Question 4
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

string ReplaceAndRemove(string s) {
  
  int write_idx = 0, a_count = 0;
  for (const char &c : s) {
    if (c != 'b') {
      s[write_idx++] = c;
    }
    if (c == 'a') {
      a_count++;
    }
  }

  s.resize(write_idx + a_count);

  int cur_idx = write_idx - 1;
  write_idx = s.size() - 1;
  while(cur_idx >= 0) {
    if (s[cur_idx] == 'a') {
      s[write_idx--] = 'd';
      s[write_idx--] = 'd';
    }
    else{
      s[write_idx--] = s[cur_idx];
    }
    --cur_idx;
  }

  return s;
}                   

int main()
{     

  string x = ReplaceAndRemove("accbbbbbca");

  cout << "RESULT: " << x << endl;
  return 0;
}