/*
* PermuteArray.cpp
* -----------------
*
* Chapter 6 Question 10
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void ApplyPermutation(vector<int> &A, vector<int> &perm)  {
    
  for (int i = 0; i < A.size(); ++i) {
    
    if (A[i] > 0) {
      int start = i;
      int curr_idx = i;
      int nextPermuteVal = A[i];
      bool cycleStarted = false;

      while (curr_idx != start || !cycleStarted) {
        int next_idx = perm[curr_idx];

        int temp = A[next_idx];

        A[next_idx] = nextPermuteVal * -1;

        curr_idx = next_idx;
        nextPermuteVal = temp;
        
        cycleStarted = true;
      }

    for (int i = 0; i < A.size(); ++i)
        cout << A[i] << " ";
      
    cout << endl;
    
    }
  }

  for (int i = 0; i < A.size(); ++i) 
    cout << endl;

}

vector<int> permute(vector<int> A, vector<int> &perm) {

  for (int i = 0; i < A.size(); i++) {
    if (perm[i] > 0) {
      int start = i;
      int curr_idx = i;
      int temp = A[i];

      do {
        int next_idx = perm[curr_idx];
        int next_temp = A[next_idx];

    
        A[next_idx] = temp;
        perm[curr_idx] *= -1;

        curr_idx = next_idx; temp = next_temp;

      } while(start != curr_idx);

    }
  }
  
  return A;
}


vector<int> cyclePermutation(int start, vector<int> &A, vector<int> &perm) {
  int curr_idx = start;
  int temp = A[curr_idx];

  do {
    int next_idx = perm[curr_idx];
    int next_temp = A[next_idx];
    A[next_idx] = temp;
    temp = next_temp;
    curr_idx = next_idx;
  } while(start != curr_idx);

  return A;
}

/**
 * To avoid modifying the sign bit in the perm array like we did in the permute() function above, we 
 * can instead only choose to permute through a cycle only if the current position we've iterated to is the 
 * leftmost position in that cycle 
 * 
 * This ensures we only permute each cycle once 
 * 
 **/
vector <int> permute2(vector<int> &A, vector<int> &perm) {  
  for (int i = 0; i < perm.size(); ++i) {
    int idx = perm[i];
    bool isMin = true;

    while (idx != i) {
      if (idx < i) {
        isMin = false;
        break;
      }

      idx = perm[idx];
    }

    if (isMin)
      A = cyclePermutation(i, A, perm);
  }

  return A;
}

int main()
{ 
    static const int arr[] = {1, 2, 3};


    static const int perm_arr[] = {2, 0,  1};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> perm(perm_arr, perm_arr + sizeof(perm_arr) / sizeof(perm_arr[0]));  
    
    vec = permute2(vec, perm);
    
    //cout << "Solution: " << test << endl;
   
    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    return 0;
}