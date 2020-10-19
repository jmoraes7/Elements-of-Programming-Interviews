/*
* FindFirstMissingPositive.cpp
* -----------------
*
* Chapter 22 Question 2
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

int FindFirstMissingPositive(vector<int>& A) {
  for (int i = 0; i < A.size(); i++) {
    int curr = A[i];
    while (A[i] > 0 && A[curr - 1] != curr) {
      std::swap(A[i], A[curr - 1]);
      curr = A[i];
    }
  }

  for (int i = 0; i < A.size(); i++) {
    if (A[i] != i + 1) {
      return i + 1;
    }
  }

  return A.size();
}

int main(int argc, char** argv) {   
  vector<int> A{3, 5, 4, -1, 5, 1, -1};
  vector<int> B{3, 4, 0, 2};


  cout << FindFirstMissingPositive(A) << endl;

  for (int x : B) {
    cout << x << " ";
  }
  
  return 0;
}


