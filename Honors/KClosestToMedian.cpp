/*
* KClosestToMedian.cpp
* -----------------
*
* Chapter 22 Question 17
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <math.h>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout; 
using std::deque;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::stoi;
using std::vector;

class Comp {
  public:
    explicit Comp(double median) : median_(median){};

    bool operator()(int a, int b) const {
      return fabs(a - median_) < fabs(b - median_);
    }

  private:
    double median_;
};

bool IsLessThan(int a, int b, int median, bool compareDistToMedian) {
  if (compareDistToMedian) {
    return fabs(a - median) < fabs(b - median);
  } else {
    return a < b;
  }
}

double GetKthLargestElement(vector<int>& A, int k, bool compareDistToMedian, double median = -1.0) {
  int start = 0, end = A.size() - 1;

  while (true) {
    int i = start, j = end;
    while (i < j) {        
      if (IsLessThan(A[i+1], A[i], median, compareDistToMedian)) {
        std::swap(A[i], A[i+1]);
        i++;
      } else {
        std::swap(A[i+1], A[j]);
        j--;
      }
    }    

    if (i  == k - 1) {
      return A[i];
    } else if (i > k - 1) {
      end = i - 1;
    } else {
      start = i + 1;
    }
  }

  return -1;
}

vector<int> GetKClosestToMedian(vector<int>& A, int k) {  
  double median = GetKthLargestElement(A, A.size() / 2, false);
  if (A.size() % 2 != 1) { // Array has even # of elements
    median = 0.5 * (median + GetKthLargestElement(A, (A.size() / 2) + 1, false));
  } 

  //nth_element(A.begin(), A.begin() + k - 1, A.end(), Comp(median));
  GetKthLargestElement(A, k, true, median);

  for (int x : A) {
    cout << x << " ";
  }
  cout << endl;

  cout << "MEDIAN: " << median << endl;

  return {A.begin(), A.begin() + k};
}

int main(int argc, char** argv) {   
  
  vector<int> A{1, 2, 10, 11, 12, 99, 100};

  auto res = GetKClosestToMedian(A, 4);
  //GetKthLargestElement(A, 4, true, 10);

  for (int x : res) {
    cout << x << " ";
  }
  cout << endl;

  return 0;
}


