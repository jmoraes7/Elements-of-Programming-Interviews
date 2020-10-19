/*
* ComputeNextPermutation.cpp
* -----------------
*
* Chapter 6 Question 11
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> NextPermutation(vector<int> perm) {

  int pivot_idx = perm.size() - 2;
  int swap_idx = 0; 
  cout << pivot_idx << endl;

  while (perm[pivot_idx] > perm[pivot_idx + 1] && pivot_idx > -1) {
    pivot_idx--;
    cout << pivot_idx << endl;

  }
  if (pivot_idx == -1) {
    return vector<int>();
  }
  
  reverse(perm.begin() + pivot_idx + 1, perm.end());

  for (int i = pivot_idx + 1; i < perm.size(); i++) {
    if (perm[i] > perm[pivot_idx]) {
      swap(perm[i], perm[pivot_idx]);
      break;
    }
  }

  // cout << "IDX " << pivot_idx << endl;
  
  // for (int i = pivot_idx; i < perm.size(); i++) {
  //   cout << perm[i] << " ";
  // }
  // cout << endl;
  
  
  return perm;
}

// vector<int> NextPermutation2(vector<int> perm) {
//   int pivot_idx = perm.size() - 2;
//   int swap_idx = 0;

//   while (perm[pivot_idx] > perm[pivot_idx + 1] && pivot_idx )
// }

int main()
{ 
    static const int arr[] = {1, 2, 3};

    static const int perm_arr[] = {3, 2, 1, 0};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> perm(perm_arr, perm_arr + sizeof(perm_arr) / sizeof(perm_arr[0]));  
    
    vec = NextPermutation(perm);
    if (vec.empty()) {
      cout << "Returned empty array" << endl;
    }
    //cout << "Solution: " << test << endl;
    
    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    return 0;
}