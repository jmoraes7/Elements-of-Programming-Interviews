/*
* RotateArray.cpp
* -----------------
*
* Chapter 22 Question 6
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

vector<int> RotateArray(vector<int> A, int k) {

  // int start_val = A[0];
  int idx = 0, tmp = A[0];
  do {
    int val_to_shift = tmp;
    int next_idx = (idx + k) % A.size();
    tmp = A[next_idx];
    A[next_idx] = val_to_shift;

    idx = next_idx;

  } while (idx != 0);

  return A;
}

int main(int argc, char** argv) {   
  
  vector<int> A = {1, 2, 3, 4, 5};
  int k = 3;

  auto res = RotateArray(A, 2);

  for (int x : res) {
    cout << x << " ";
  }

  return 0;
}


