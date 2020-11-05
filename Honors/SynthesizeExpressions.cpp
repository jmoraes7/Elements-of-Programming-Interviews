/*
* SynthesizeExpressions.cpp
* -----------------
*
* Chapter 22 Question 33
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "./DoublyLinkedList.h"

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::greater;
using std::hash;
using std::istringstream;
using std::length_error;
using std::make_unique;
using std::unique_ptr;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::stoi;
using std::unordered_map;
using std::unordered_set;
using std::vector;

static vector<char> operators{'+', '*', '-'};

/**
* O(4^n)
*/
void SynthExpressionHelper(string prefix, string suff, int val_so_far, int target,
                  vector<string>* expressions) {
  if (suff == "" && val_so_far == target) {
    // cout << "Curr Prefix: " << prefix << " Suffix: " << suff << " Val: " << val_so_far << endl;

    (*expressions).emplace_back(prefix);
  }
  

  for (int i = 0; i < suff.size(); i++) {
    
    string s = suff.substr(0, i + 1);
    int next_num = stoi(s);

    string next_suff = suff.substr(i+1);

    // cout << "Curr Prefix: " << prefix << " Next Num: " << s << " Next Suffix: " << next_suff << " Val: " << val_so_far << endl;
    
    if (prefix == "") {
      SynthExpressionHelper(s, next_suff, next_num, target, expressions);
    } else  {
      for (const auto& c : operators) {
        if (c == '+') {
            SynthExpressionHelper(prefix + '+' + s, next_suff, val_so_far + next_num, target, expressions);
        } else if (c == '*') {
            SynthExpressionHelper(prefix + '*' + s, next_suff, val_so_far * next_num, target, expressions);
        } else {
           SynthExpressionHelper(prefix + '-' + s, next_suff, val_so_far - next_num, target, expressions);
        }
      } 
    }
  } 
}

vector<string> SynthesizeExpressions(string num, int target) {
  vector<string> expressions;

  SynthExpressionHelper("", num, 0, target, &expressions);

  return expressions;
}

int main(int argc, char** argv) {   

  string num = "1234";
  int target = 10;

  auto res = SynthesizeExpressions(num, target);
  cout << "NUM: " << num << " Target: " << target << endl;
  for (string s : res) {
    cout << s << endl;
  }
  cout << endl;
  

  num = "4321";
  res = SynthesizeExpressions(num, target);
  
  cout << "NUM: " << num << " Target: " << target << endl;
  for (string s : res) {
    cout << s << endl;
  }

  return 0;
}


