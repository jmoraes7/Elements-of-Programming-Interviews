/*
* GenerateMatchedParens.cpp
* -----------------
*
* Chapter 16 Question 7
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

void GenerateMatchedParensHelper(string partial_str, int n, int num_left_parens, 
                                  int num_right_parens, vector<string>& parens) {
  if (num_left_parens > n || num_right_parens > n || num_right_parens > num_left_parens) {
    return;
  }

  if (num_left_parens == n && num_right_parens == n) {
    parens.push_back(partial_str);
    return;
  }

  //try adding left parens
  GenerateMatchedParensHelper(partial_str + "(", n, num_left_parens + 1, num_right_parens, parens);

  //try adding right parens
  GenerateMatchedParensHelper(partial_str + ")", n, num_left_parens, num_right_parens + 1, parens);

}

vector<string> GenerateMatchedParens(int n) {
  vector<string> parens;

  GenerateMatchedParensHelper("", n, 0, 0, parens);

  return parens;
}

/*
* Book Solution
*/ 

void DirectedGenerateBalancedParentheses(int num_left_parens_needed,
                                         int num_right_parens_needed,
                                         const string valid_prefix,
                                         vector<string>& result) {
  
  if (!num_left_parens_needed && !num_right_parens_needed) {
    result.push_back(valid_prefix);
    return;
  } 

  if (num_left_parens_needed > 0) {
    DirectedGenerateBalancedParentheses(num_left_parens_needed - 1,
                                        num_right_parens_needed,
                                        valid_prefix + "(",
                                        result);
  }

  if (num_left_parens_needed < num_right_parens_needed) {
    DirectedGenerateBalancedParentheses(num_left_parens_needed,
                                        num_right_parens_needed - 1,
                                        valid_prefix + ")",
                                        result);
  }
}


int main(int argc, char* argv[]) {
  vector<int> arr{1, 2, 3, 4, 5};

  auto parens = GenerateMatchedParens(3);

  for (string paren : parens) { 
    
    cout << paren << endl;
    
  }

  return 0;
}
