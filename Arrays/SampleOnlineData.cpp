/*
* SampleOnlineData.cpp
* -----------------
*
* Chapter 6 Question 13
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector <int> getReservoirSample(vector<int> &arr, int size) {  
  srand(time(0));
  vector<int> running_sample;
  
  for (int i = 0; i < size; i++) {
    running_sample.push_back(arr[i]);
  }

  for (int i = size; i < arr.size(); i++) {
    int idx_to_replace = (std::rand() % static_cast<int>(i));
    cout << idx_to_replace << endl;
    
    if (idx_to_replace < size) {
      running_sample[idx_to_replace] = arr[i];
    }
  }

  return running_sample;
}

int main()
{ 
    static const int arr[] = {3, 7, 5, 11};

    static const int perm_arr[] = {3, 2, 1, 0};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> perm(perm_arr, perm_arr + sizeof(perm_arr) / sizeof(perm_arr[0]));  
    
    vec = getReservoirSample(vec, 3);
    
    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    return 0;
}