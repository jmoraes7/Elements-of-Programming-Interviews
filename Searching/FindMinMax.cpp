/*
* FindMinMax.cpp
* -----------------
*
* Chapter 12 Question 8
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

struct MinMax {
  int min, max;
};

MinMax getMinMax(int a, int b) {
  MinMax result{std::min(a,b), std::max(a,b)};

  return result;    
}

/*
* Takes (3n/2) - 2 comparisons rather than the 2(n-1) comparisons required from the naive approach  
*/
MinMax FindMinMax(vector<int> A) {
  MinMax globalMinMax;

  if (A.size() <= 1) {
    globalMinMax.min = A.front();
    globalMinMax.max = A.front();
  }
  
  globalMinMax = getMinMax(A[0], A[1]);

  for (int i = 2; i < A.size() - 1; i += 2) {
    MinMax localMinMax = getMinMax(A[i], A[i+1]);

    globalMinMax = {std::min(globalMinMax.min, localMinMax.min),
                    std::max(globalMinMax.max, localMinMax.max)};
  }

  //if odd # of elements, the last elem hasn't been processed
  if (A.size() % 2 == 1) {
    globalMinMax = {std::min(globalMinMax.min, A.back()),
                    std::max(globalMinMax.max, A.back())};
  }

  //for (int i = 2)
  
  return globalMinMax;
}

int main(int argc, char** argv) {
  vector<int> A{3, 2, 5, 1, 2, 4, -7};

  MinMax result = FindMinMax(A);

  cout << "MIN: " << result.min << " - MAX: " << result.max << endl;

  return 0;
}
