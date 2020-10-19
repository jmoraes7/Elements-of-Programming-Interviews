/*
* TestCollatzConjecture.cpp
* -----------------
*
* Chapter 13 Question 15
*/

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::greater;
using std::ifstream;
using std::istringstream;
using std::list;
using std::ofstream;
using std::priority_queue;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

/*
* Failure conditions: 
*   1. sequence returns to a previous number in the sequence, which means it's fallen into a loop
*   2. sequence continues until infinity (test by checking for overflow)
*
*/
bool TestCollatzConjecture(int n) {
  unordered_set<long> verified_numbers; //restrict to odd numbers to save space
  verified_numbers.insert(1); 

  for (int i = 2; i <= n; i++) {
    unordered_set<long> sequence;
    int test_i = i;

    while (test_i >= i) {
      if (sequence.count(test_i)) {
        //We've encountered test_i already so the sequnce has fallen into a loop
        //This disproves the hypothesis
        return false;
      }
      
      sequence.insert(test_i);

      if (test_i % 2) {
        if (verified_numbers.count(test_i)) {
          verified_numbers.insert(i);
          break;
        }

        long next_test_i = 3 * test_i + 1;
        if (next_test_i <= test_i) { //overflow occurred
          throw std::overflow_error("Collatz sequence overflow for " + std::to_string(i));
        }
        
        test_i = next_test_i;
      } else {
        test_i /= 2;
      }

    }
  }

  return true;
}

int main(int argc, char** argv) {    
  int n = 113382;

  cout << TestCollatzConjecture(n) << endl;

  return 0;
}
