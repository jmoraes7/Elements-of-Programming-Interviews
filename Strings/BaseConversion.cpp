/*
* BaseConversion.cpp
* -----------------
*
* Chapter 7 Question 2
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

string convertBase(string s, int b1, int b2) {
  bool isNegative = s.front() == '-';
  int x = 0;
  for (size_t i = (isNegative ? 1 : 0); i < s.size(); ++i) {
    x *= b1;
    x += isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;  
  }

  string result;
  do {
    int remainder = x % b2;
    result += remainder >= 10 ? remainder - 10 + 'A' : remainder + '0';
    x /= b2;
  } while(x);

  if (isNegative) {
    result += '-';
  }

  reverse(result.begin(), result.end());

  return result;
}

int main()
{     
  int x = -123;
  string s = "-615";

  //string s = intToString(x);
  //cout << "String: " << s << endl;

  s = convertBase(s, 7, 13);

  cout << "RESULT: " << s << endl;
  return 0;
}