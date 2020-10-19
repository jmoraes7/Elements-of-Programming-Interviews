/*
* RomanToInteger.cpp
* -----------------
*
* Chapter 7 Question 9
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

static unordered_map<char, int> map = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

int RomanToInteger(const string& s) {
  
  int num = 0;
  for (int i = 0; i < s.size(); ++i) {
    int curr = map[s[i]];
    
    if (i + 1 < s.size() && map[s[i]] < map[s[i+1]]) {
      curr = map[s[i+1]] - map[s[i]];
      ++i;
    }
    
    num += curr;
  }

  return num;
}

int RomanToIntegerClean(const string& s) {
  int sum = map[s.back()];

  for (int i = s.size() - 2; i > -1; --i) {
    if (map[s[i]] < map[s[i+1]]) {
      sum -= map[s[i]];
    } else { 
      sum += map[s[i]];
    }
  }

  return sum;
}

int main()
{     
  int num = RomanToIntegerClean("LIV");

  cout << num << endl;

  return 0;
}