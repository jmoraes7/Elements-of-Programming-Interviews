/*
* SpreadsheetColumnEncoding.cpp
* -----------------
*
* Chapter 7 Question 3
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

int SSDecodeID(string s) {
  
  int rowID = 0;
  
  for (const char &c: s) {
    rowID = rowID * 26 + c - 'A' + 1;
  }
  return rowID;
}

int main()
{     
  string s = "AB";

  //string s = intToString(x);
  //cout << "String: " << s << endl;

  int x = SSDecodeID(s);

  cout << "RESULT: " << x << endl;
  return 0;
}