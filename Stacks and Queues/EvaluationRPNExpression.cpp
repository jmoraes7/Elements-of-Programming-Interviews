/*
* EvaluateRPNExpression.cpp
* -----------------
*
* Chapter 9 Question 2
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

int eval(const string& RPN_expression) {
  stack<int> intermediate_results;

  stringstream ss(RPN_expression);
  string token;
  const char delimiter = ',';

  while (getline(ss, token, delimiter)) {
    if (token == "+" || token == "-" || token == "x" || token == "/") {
      int y = intermediate_results.top();
      intermediate_results.pop();
      int x = intermediate_results.top();
      intermediate_results.pop();

      switch(token.front()) {
        case '+':
          intermediate_results.push(x + y);
          break;
        case '-':
          intermediate_results.push(x - y);
          break;
        case 'x':
          intermediate_results.push(x * y);
          break;
        case '/':
          intermediate_results.push(x / y);
          break;
      }
      
    } else {
      intermediate_results.push(stoi(token));
    }
  }

  return intermediate_results.top();
}


int main()
{  
  string expression = "3,4,+,2,x,1,+";
  //expression = "1,1,+,-2,x";

  std::cout << eval(expression) << endl;

  return 0;
}