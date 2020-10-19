/*
* InterconvertStringsAndInt.cpp
* -----------------
*
* Chapter 7 Question 1
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

string intToString(int x) {
  bool isNegative;
  if (x < 0) {
    x = -x, isNegative == true;
  }

  string s;
  do { 
    s += '0' + x%10;
    x /= 10;

  } while(x);

  if (isNegative) {
    s += '-';
  } 

  reverse(s.begin(), s.end());

  return s;
}

int stringToInt(string s) {
  int x = 0;
  bool isNegative = s[0] == '-';

  for (int i = isNegative ? 1 : 0; i < s.size(); ++i) {
    int digit = s[i] - '0';
    x = 10*x + digit;
  }

  return isNegative ? -x : x;
}

int main()
{     
  int x = -123;
  string s = "-123598";

  //string s = intToString(x);
  //cout << "String: " << s << endl;

  x = stringToInt(s);

  cout << "Int: " << x << endl;
  return 0;
}