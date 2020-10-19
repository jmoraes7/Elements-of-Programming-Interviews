/*
* ComputeRandomPermutation.cpp
* -----------------
*
* Chapter 6 Question 14
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "./SampleOfflineData.h"

using namespace std;

vector <int> computeRandomPermutation(int n) {  
  vector <int> permutation(n);
  iota(permutation.begin(), permutation.end(), 0);
  getRandomSample(permutation, permutation.size());

  return permutation;
}

int main()
{ 
    static const int arr[] = {3, 7, 5, 11};

    static const int perm_arr[] = {3, 2, 1, 0};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> perm(perm_arr, perm_arr + sizeof(perm_arr) / sizeof(perm_arr[0]));  
    
    vec = computeRandomPermutation(4);
    
    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    return 0;
}