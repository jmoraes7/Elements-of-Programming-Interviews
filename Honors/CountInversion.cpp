/*
* CountInversions.cpp
* -----------------
*
* Chapter 22 Question 34
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::greater;
using std::hash;
using std::istringstream;
using std::length_error;
using std::make_unique;
using std::unique_ptr;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::stoi;
using std::unordered_map;
using std::unordered_set;
using std::vector;

vector<std::pair<int, int> > CountInversions(vector<int> A) {
  vector<std::pair<int, int> > results;
  
  for (int i = 0; i < A.size(); i++) {
    for (int j = i + 1; j < A.size(); j++) {
      if (A[i] > A[j]) {
        results.emplace_back(A[i], A[j]);
      }
    }
  }
  
  return results;
}

int merge(vector<int>* arr, int start, int mid, int end) {
  vector<int> arr1(mid - start + 1, 0);
  vector<int> arr2(end - mid, 0); 
  
  for (int i = 0; i < arr1.size(); i++) {
    arr1[i] = (*arr)[start + i];
  }

  for (int i = 0; i <= arr2.size(); i++) {
    arr2[i] = (*arr)[mid + 1 + i];
  }

  int inversions = 0;
  int i = 0, j = 0;
  while (i < arr1.size() && j < arr2.size()) {
    if (arr1[i] <= arr2[j]) {
      (*arr)[start] = arr1[i++];
    } else {
      (*arr)[start] = arr2[j++];
      inversions += arr1.size() - i;
    }
    start++;
  }

  while (i < arr1.size()) {
    (*arr)[start++] = arr1[i++];
  }

  while(j < arr2.size()) {
    (*arr)[start++] = arr2[j++];
  }

  return inversions;
}

int CountInversions(vector<int>* arr, int start, int end) {  
  int count = 0;
  if (start < end) {
    int mid = start + ((end - start) / 2);

    count += CountInversions(arr, start , mid);
    count += CountInversions(arr, mid + 1, end);
    count += merge(arr, start, mid, end);
  }
  return count;
}

int main(int argc, char** argv) {   

  vector<int> A{1, 2, 0, 3, 5,};

  for (int x : A) {
    cout << x << " ";
  }
  cout << endl;

  cout << "There are " << CountInversions(&A, 0, A.size() - 1) << " inversions" << endl;

  return 0;
}


