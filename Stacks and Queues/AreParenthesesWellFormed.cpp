/*
* AreParenthesesWellFormed.cpp
* -----------------
*
* Chapter 9 Question 3
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>

using namespace std;

using std::length_error;
using std::max;
using std::stack;

bool isWellFormed(const string& s) {
  stack <char> left_chars;

  for (int i = 0; i < s.size(); ++i)  {
    if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
      left_chars.push(s[i]);
    }
    else { 
      if (left_chars.empty()) {
        return false;
      }

      if ((s[i] == ')' && left_chars.top() != '(') ||
          (s[i] == '}' && left_chars.top() != '{') ||
          (s[i] == ']' && left_chars.top() != '[')) {
            return false;
      }

      left_chars.pop();
    }
  }

  return left_chars.empty();
}


int main()
{  
  string expression = "[[({})[{{}}]]";
  //expression = "1,1,+,-2,x";

  std::cout << isWellFormed(expression) << endl;

  return 0;
}