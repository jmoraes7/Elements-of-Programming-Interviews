/*
* PairSumAbsSortedArray.cpp
* -----------------
*
* Chapter 22 Question 44
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

template <typename Comp>
std::pair<int, int> getPairSumUsingComp(vector<int> arr, int k, Comp comp) {
  
  int i = 0, j = arr.size() - 1;
  while (i < j) {
    while (comp(arr[i], 0)) {
      cout << i << " HERE" << endl;
      i++;
    }

    while (comp(arr[j], 0)) {
      j--;
    }

    cout << arr[i] <<  " " << arr[j] << endl;
    if (arr[i] + arr[j] == k) {
      return {i, j};
    } else if (comp(arr[i] + arr[j], k)) {
      i++;
    } else {
      j--;
    }
  }

  return {-1, -1};
}

std::pair<int, int> getNegativePositivePairSum(vector<int> arr, int k) {
  int i = arr.size() - 1, j = arr.size() - 1;

  std::pair<int, int> res(-1, -1);
  while  (i >= 0 && j >= 0) {
    
    while (arr[i] > 0) {
      if (i < 0)  return res;
      i--;
    } 

    while (arr[j] <= 0) {
      if (j < 0)  return res; 
      j--;
    }

    if (arr[i] + arr[j] == k) {
      return {i, j};
    } else if (arr[i] + arr[j] > k) {
      j--;
    } else {
      i--;
    }
  }

  return res;
}

std::pair<int, int> getPairSumAbsSortedArray(vector<int> arr, int k) {
  std::pair<int, int> res = getNegativePositivePairSum(arr, k);

  if (res.first == -1 && res.second == -1) {
    return -k >= 0 ? getPairSumUsingComp(arr, k, std::less<int>()) : 
                    getPairSumUsingComp(arr, k, std::greater<int>());
  } 
  return res;
}

int main(int argc, char** argv) {   

  vector<int> arr{-49, 75, 103, -147, 164, -197, -238, 314, 348, -422};

  auto res = getPairSumAbsSortedArray(arr, 167);

  cout << res.first << " " << res.second << endl;

  return 0;
}


