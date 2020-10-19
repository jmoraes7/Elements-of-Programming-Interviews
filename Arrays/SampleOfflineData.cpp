/*
* SampleOfflineData.cpp
* -----------------
*
* Chapter 6 Question 12
*/

#include <iostream>
#include "SampleOfflineData.h"

using namespace std;

using std::default_random_engine;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

vector<int> getRandomSample(vector<int> &arr, int size) {  
  srand(time(0));
  
  for (int i = 0; i < size; i++) {
    
    int rand = i + (std::rand() % static_cast<int>(arr.size() - i));
    // cout << rand << endl;
    swap(arr[i], arr[rand]);
  }

  return arr;
}

// int main()
// { 
//     static const int arr[] = {3, 7, 5, 11};

//     static const int perm_arr[] = {3, 2, 1, 0};

//     vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
//     vector<int> perm(perm_arr, perm_arr + sizeof(perm_arr) / sizeof(perm_arr[0]));  
    
//     vec = getRandomSample(vec, 3);
    
//     for (int i = 0; i < vec.size(); i++) 
//         cout << vec[i] << " ";
    
//     return 0;
// }