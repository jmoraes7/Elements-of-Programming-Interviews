/*
* FindBiggestNMinusOneProduct.cpp
* -----------------
*
* Chapter 22 Question 4
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::array;
using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::random_device;
using std::stoul;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

int FindBiggestNMinusOneProduct(vector<int> A) {
  int prod = 1;
  for (int i = 0; i < A.size() - 1; i++) {
    prod *= A[i];
  }

  int max_prod = prod;
  for (int i = A.size() - 1; i > 0; i--) {
    prod *= A[i];
    prod /= A[i-1];
    if (prod > max_prod) {
      max_prod = prod;
    }
  }

  return max_prod;
}

int main(int argc, char** argv) {   
  
  vector<int> A = {3, 2, -1, 4};

  cout << FindBiggestNMinusOneProduct(A) << endl;

  return 0;
}


