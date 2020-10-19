/*
* BinarySearch.cpp
* -----------------
*
* Binary Search Implementation
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int binarySearch(int target, vector<int> &nums) {
    
    int left = 0;
    int right = nums.size() - 1;

    int count = 0;
    while (left <= right) {
        //this prevents Integer overflow as opposed to setting mid = (right + left) / 2
        int mid = left + (right - left) / 2; 
       
        cout << "Midpoint: " << mid << " Left: " << left << " Right: " << right << " LOOKING AT: " << nums[mid] << endl;

        if (nums[mid] < target) left = mid + 1;

        else if (nums[mid] > target) right = mid - 1;

        else return mid;

        count++;
        if (count == 6) break;
    }
    return -1;
}


int main() {
  
  vector<int> nums(10);
    iota(nums.begin(), nums.end(), 0);

  for (int x: nums) {
      cout << x << " "; 
  }
  cout<<endl;

  int target_idx = binarySearch(9, nums);

  cout << target_idx << endl;
  
  return 0;
}