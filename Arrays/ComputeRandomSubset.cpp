/*
* ComputeRandomSubset.cpp
* -----------------
*
* Chapter 6 Question 15
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>


using namespace std;

using std::default_random_engine;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

/*
* There are n choose k possible subsets or n! / ((n-k)! * k!)
* Need to design algorithm that returns any one of these subsets with equal probability
*
* The key to reducing space complexity to O(K) is using a hashtable
* to mimic 'Sample offline data'
*/

vector<int> getRandomSubset(int n, int k) {
  unordered_map<int, int> hashtable;
  default_random_engine seed((random_device())());
  
  for (int i = 0; i < k; ++i) {
    //generate random number in [i, n-1]
    uniform_int_distribution<int> rand_idx_gen(i, n-1);
    int rand_idx = rand_idx_gen(seed);

    auto ptr1 = hashtable.find(rand_idx), 
         ptr2 = hashtable.find(i);
 
    if (ptr1 == hashtable.end() && ptr2 == hashtable.end()) {
      hashtable[rand_idx] = i;
      hashtable[i] = rand_idx;
    } else if (ptr1 == hashtable.end() && ptr2 != hashtable.end()) {
      hashtable[rand_idx] = ptr2->second;
      ptr2->second = rand_idx;
    } else if (ptr1 != hashtable.end() && ptr2 == hashtable.end()) {
      hashtable[i] = ptr1->second;
      ptr1->second = i;
    } else {
      int temp = ptr1->second;
      ptr1->second = ptr2->second;
      ptr2->second = temp;
    }
  }

  vector<int> subset(k);
  for (int i = 0; i < k; ++i) {
    subset[i] = hashtable[i];
  }

  return subset;
}

int main()
{ 
    static const int arr[] = {1, 2, 3};


    static const int perm_arr[] = {2, 0,  1};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> perm(perm_arr, perm_arr + sizeof(perm_arr) / sizeof(perm_arr[0]));  
    
    vec = getRandomSubset(100, 4);
    
    //cout << "Solution: " << test << endl;
    cout << "VEC SIZE: " << vec.size() << endl;
    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    return 0;
}