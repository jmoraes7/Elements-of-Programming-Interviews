/*
* FindCelebrity.cpp
* -----------------
*
* Chapter 19 Question 1
*/

#include <cassert>
#include <deque>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::max;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

int FindCelebrity(const vector<deque<bool> >& F) {
  int i = 0, j = F.size() - 1;

  while (i < j) {
    if (F[i][j]) {
      i++;
    } else {
      j--;
    }
  }

  return i;
}

int CalculateLargestRectangleClean(vector<int>& heights) {

}

int main(int argc, char** argv) {   
  vector<deque<bool> > F{{false, true, false, true, false},
                           {false, false, true, true, false},
                           {false, false, false, true, true},
                           {false, false, false, false, false},
                           {true, false, false, true, false}};
  assert(FindCelebrity(F) == 3);

  return 0;
}


