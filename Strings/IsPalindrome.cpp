/*
* IsPalindrome.cpp
* -----------------
*
* Chapter 7 Question 5
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

bool isPalindrome(const string &s) {
  int i = 0, j = s.size() - 1; 

  while (i < j) {

    while (!isalnum(s[i]) && i < j) {
      ++i;
    }

    while (!isalnum(s[j]) && i < j) {
      --j;
    }

    if (tolower(s[i]) != tolower(s[j]) ) {
      return false;
    }

    ++i, --j;
  }
  return true;
}   

int main()
{     
  bool result = isPalindrome("A man, a plan, a canal, Panama");

  cout << "RESULT: " << result << endl;
  return 0;
}