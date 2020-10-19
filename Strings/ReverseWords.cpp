/*
* ReverseWords.cpp
* -----------------
*
* Chapter 7 Question 6
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

string reverseWords(string result) {

  reverse(result.begin(), result.end());
  //reverse(result.begin() + 4, result.begin() + 9);

  int idx = 0;
  for (int i = 0; i < result.size(); ++i) {
    if (result[i] == ' ' || i == result.size() - 1) {

      auto start_idx = result.begin() + idx;
      auto end_idx = i == result.size() - 1 ? result.begin() + i + 1 : result.begin() + i;

      reverse(start_idx, end_idx);
      idx = i + 1;
    }
  }
                                 
  return result;
}   

string reverseWords2(string result) {
  reverse(result.begin(), result.end());

  int start = 0, end = 0;
  while ((end = result.find(" ", start)) != string::npos) {
    reverse(result.begin() + start, result.begin() + end);
    start = end + 1;
    
  }

  reverse(result.begin() + start, result.end());
  
  return result;
}



int main()
{     
  string result = reverseWords2("Alice likes Bob and Me");

  cout << "RESULT: " << result << endl;
  return 0;
}