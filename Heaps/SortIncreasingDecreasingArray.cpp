/*
* SortIncreasingDecreasingArray.cpp
* -----------------
*
* Chapter 11 Question 2
*/

#include <cassert>
#include <iostream>
#include <list>
#include <queue>
#include <iterator>

#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./MergeSortedArray.h"

using namespace std;

vector<int> SortKIncreasingDecreasingArray(const vector<int>& array){
  vector<vector<int> > sorted_subarrays;

  typedef enum { INCREASING, DECREASING } SubarrayType;
  SubarrayType subarray_type = INCREASING;

  int start_idx = 0;
  for (int i = 1; i <= array.size(); ++i) {

    if (i == array.size() ||
        (array[i-1] < array[i] && subarray_type == DECREASING) || 
        (array[i-1] >=  array[i] && subarray_type == INCREASING)) {

      vector<int>subarray(i - start_idx);

      if (subarray_type == DECREASING) {
        copy(array.rbegin() + array.size() - i, array.rbegin() + array.size() - start_idx, subarray.begin());
        
        // cout << "DECREASING: " << endl;
        // for (int x : subarray) {
        //   cout << x << " ";
        // }
        // cout << endl;
      } else {
        copy(array.begin() + start_idx, array.begin() + i, subarray.begin());

        // cout << "INCREASING: " << endl;
        // for (int x : subarray) {
        //   cout << x << " ";
        // }
        // cout << endl;
      }
      sorted_subarrays.push_back(subarray);

      start_idx = i;
      subarray_type = (subarray_type == INCREASING ? DECREASING : INCREASING);
    }
  }
  
  return MergeSortedArrays(sorted_subarrays);
}

void SimpleTest() {
   vector<int> A{1, 2, 3, 2, 1, 4, 5, 10, 9, 4, 4, 1, -1};
  auto ans = SortKIncreasingDecreasingArray(A);
  assert(ans.size() == A.size() && is_sorted(ans.cbegin(), ans.cend()));

  A = {numeric_limits<int>::min(), -1, 0, 1, 2, 4, 8,
       numeric_limits<int>::max()};
  ans = SortKIncreasingDecreasingArray(A);
  assert(ans.size() == A.size() && is_sorted(ans.cbegin(), ans.cend()));

  reverse(A.begin(), A.end());
  ans = SortKIncreasingDecreasingArray(A);
  assert(ans.size() == A.size() && is_sorted(ans.cbegin(), ans.cend()));
}

int main(int argc, char* argv[]) {
  SimpleTest();
  
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    vector<int> A;
    cout << "n = " << n << endl;
    uniform_int_distribution<int> dis(-999999, 999999);
    generate_n(back_inserter(A), n, [&] { return dis(gen); });
    vector<int> ans = SortKIncreasingDecreasingArray(A);
    /*
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    */
    assert(ans.size() == A.size());
    assert(is_sorted(ans.cbegin(), ans.cend()));
  }
  
  return 0;
}