/*
* LongestSubstringOfMatchedParentheses.cpp
* -----------------
*
* Chapter 22 Question 13
*/

#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::shared_ptr;
using std::stack;
using std::stoi;
using std::string;

//"((())()(()(";

// 1 - 3

int Parse(const string& s, char paren, int begin, int end, int dir) {
  int max_length = 0, num_parens_so_far = 0, length = 0;
  cout << "HERE " << endl;
  for (int i = dir * begin; i <= end; ++i) {
    if (s[dir * i] == paren) {
      ++num_parens_so_far, ++length;
    } else {  // s[dir * i] != paren
      cout << max_length << " " << length << endl;
      if (num_parens_so_far <= 0) {
        num_parens_so_far = length = 0;
      } else {
        --num_parens_so_far, ++length;
        if (num_parens_so_far == 0) {
          cout << length << endl;
          max_length = std::max(max_length, length);
        }
      }
    }
  }

  cout << "MAX: " << max_length << endl;
  return max_length;
}

int ParseFromLeft(const string& s) {
  return Parse(s, '(', 0, s.size() - 1, 1);
}

int ParseFromRight(const string& s) {
  return Parse(s, ')', s.size() - 1, 0, -1);
}

int LongestValidParentheses(const string& s) {
  cout << "PARSE Right: " << ParseFromRight(s) << endl;
  return 0;//std::max(ParseFromLeft(s), ParseFromRight(s));
}

std::pair<int, int> LongestSubstringOfMatchedParentheses(string str) {
  std::pair<int, int> indices = {-1, -1};

  int end = -1;
  stack<int> left_parentheses_indices;
  for (int i = 0; i < str.size(); i++) {
    if ( str[i] == '(') {
      left_parentheses_indices.push(i); 
    } else if(left_parentheses_indices.empty()) {
        end = i;
    } else {
      left_parentheses_indices.pop();
      
      int start = left_parentheses_indices.empty() ?
                  end : 
                  left_parentheses_indices.top();


      int len = i - start;
      if (len > indices.second - indices.first) {
        indices = {i - len + 1, i};
      }
    }
    
  }

  return indices;
}

int main(int argc, char** argv) {   
  
  string str = "((())()(()("; //")((())())))"

  auto substr_idx = LongestSubstringOfMatchedParentheses(str);

  cout << substr_idx.first << " " << substr_idx.second << endl;

  //int len = LongestValidParentheses(str);

  // cout << len << endl;

  //cout << substr_idx.first << " " << substr_idx.second << endl;

  cout << endl;
    
  return 0;
}


