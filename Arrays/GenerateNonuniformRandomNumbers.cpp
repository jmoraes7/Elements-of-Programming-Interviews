/*
* GenerateNonuniformRandomNumbers.cpp
* -----------------
*
* Chapter 6 Question 16
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

int getIndex(vector<double> &distribution, double target) {
  int left = 0;
  int right = distribution.size() - 1;
  int mid = -1;

  //binary search
  while (left <= right) {

    mid = left + (right - left) / 2; //prevent integer overflow

    if (distribution[mid] <= target) left = mid + 1;
    else if (distribution[mid-1] > target)  right = mid - 1;
    else break;
  }

  return mid;
}

int getNonUniformRandomNumber(vector<int> &values, vector<double> &probs) {
  default_random_engine seed((random_device())());

  vector<double> distribution(probs.size()+1);
  for (int i = 1; i < distribution.size(); ++i) {
    distribution[i] = probs[i-1] + distribution[i-1];
    cout << distribution[i] << " ";
  }
  cout << endl;

  double num = generate_canonical<double, numeric_limits<double>::digits>(seed);
  cout << "NUM: " << num << endl;

  int index = getIndex(distribution, num);

  cout << "Index: " << index << " " << distribution[index] << endl;

  return values[index-1];
}

int getNonUniformRandomNumber2(vector<int> &values, vector<double> &probs) {
  default_random_engine seed((random_device())());

  vector<double> prob_sums;
  prob_sums.push_back(0.0);

  partial_sum(probs.cbegin(), probs.cend(), back_inserter(prob_sums));

  double num = generate_canonical<double, numeric_limits<double>::digits>(seed);

  //distance(arg1, arg2) counts the number of elements between arg1 and arg2
  //upper_bound() returns the last position in the vector that 'num' could be inserted in 
  //               without changing the ordering of the rest of the elements
  int interval_idx = distance(prob_sums.cbegin(), 
                        upper_bound(prob_sums.cbegin(), prob_sums.cend(), num)) - 1;
    
  cout << "NUM: " << num << " INDEX: " << interval_idx << endl;
  for (double x : prob_sums) {
    cout << x << " ";
  }

  cout << endl;

  return values[interval_idx];

}


int main()
{ 
    static const int arr[] = {1, 2, 3, 4};
    static const double perm_arr[] = {0.25, 0.25,  0.24, 0.26};
    //static const double perm_arr[] = {0.5, 0.1666665, 0.1666665, 0.111111, 0.0555556};

    

    vector<int> values(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<double> probs(perm_arr, perm_arr + sizeof(perm_arr) / sizeof(perm_arr[0]));  
    
    int val = getNonUniformRandomNumber2(values, probs);
    
    cout << val << endl;
    
    return 0;
}