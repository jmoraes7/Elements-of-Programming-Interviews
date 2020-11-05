/*
* LongestSubarrayLessThanK.cpp
* -----------------
*
* Chapter 22 Question 46
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::min;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

std::pair<int, int> getLongestSubarrayLessThanK(vector<int> arr, int k) {
  vector<int> prefix_sum;
  partial_sum(arr.cbegin(), arr.cend(), back_inserter(prefix_sum));
  
  cout << "PREFIX SUM: " << endl;
  for (int x : prefix_sum) {
    cout << x << " ";
  }
  cout << endl << endl;

  if (prefix_sum.back() < k) {
    return {0, arr.size() - 1};
  }

  vector<int> min_prefix_sum(arr.size());
  min_prefix_sum.back() = prefix_sum.back();
  for (int i = min_prefix_sum.size() - 2; i >= 0; i--) {
    min_prefix_sum[i] = std::min(min_prefix_sum[i+1], prefix_sum[i]);
  }

  cout << "MIN PREF SUMS: " << endl;
  for (int x : min_prefix_sum) {
    cout << x << " ";
  }


  std::pair<int, int> res_idx(-1, -1);
  int a = 0, b = 0, max_length = 0;
  while (a < arr.size() && b < arr.size()) {
    int min_curr_sum = a > 0 ? min_prefix_sum[b] - prefix_sum[a - 1] : min_prefix_sum[b];
     
    if (min_curr_sum <= k) {
      int curr_length = b - a + 1;
      if (curr_length > max_length) {
        max_length = curr_length;
        res_idx = { a, b };
      }
      b++;
    } else { //min_curr_sum > k
      a++;
    }
  }
  return res_idx;
}

int main(int argc, char** argv) {   

  vector<int> arr{431, -15, 639, 342, -14, 565, -924, 635, 167, -70};
  int k = 185;

  auto res = getLongestSubarrayLessThanK(arr, k);

  cout << res.first << " " << res.second << endl;


  // 431 416 1055 1397 1383 1948 1024 1659 1826 1756 
  // 431 416 1024 1024 1024 1024 1024 1659 1756 1756 

  // 431 416 1055 1397 1383 1948 1024 1659 1826 1756 
  // -15 624 966 952 1517 593 1228 1395 1325 
  // 639 981 967 1532 608 1243 1410 1340 
  // 342 328 893 -31 604 771 701 
  // -14 551 -373 262 429 359 
  // 565 -359 276 443 373 
  // -924 -289 -122 -192 
  // 635 802 732 
  // 167 97 
  // -70 

  return 0;
}


