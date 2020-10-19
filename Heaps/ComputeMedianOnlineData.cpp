/*
* ComputeMedianOnlineData.cpp
* -----------------
*
* Chapter 11 Question 5
*/

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::greater;
using std::istringstream;
using std::less;
using std::priority_queue;
using std::random_device;
using std::string;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

vector<double> global_result;

void OnlineMedian(istringstream* sequence) {
  priority_queue<int, vector<int> > max_heap;
  priority_queue<int, vector<int>, greater<int> > min_heap;

  int x;
  while (*sequence >> x) {
    if (max_heap.empty()) {
      max_heap.push(x);
    } else {
      if (x <= max_heap.top()) {
        max_heap.push(x);
      } else {
        min_heap.push(x);
      }
    }

    //ensure min_heap and max_heap have equal # of elements if an even # of elements is read
    //otherwise ensure that max_heap has one more element than min_heap
    if (max_heap.size() > min_heap.size() + 1) {
      min_heap.push(max_heap.top());
      max_heap.pop();
    } else if (min_heap.size() > max_heap.size()) {
      max_heap.push(min_heap.top());
      min_heap.pop();
    }

    double median = min_heap.size() == max_heap.size() ?
                  0.5 * (min_heap.top() + max_heap.top()) :
                  max_heap.top();

    global_result.push_back(median);
  }
}

void SimpleTest() {
  istringstream sequence("5 4 3 2 1");
  OnlineMedian(&sequence);
  vector<double> golden{5, 4.5, 4, 3.5, 3};

  for (double x : global_result) {
    cout << x << " ";
  }
  cout << endl;
  assert(equal(golden.begin(), golden.end(), global_result.begin(),
               global_result.end()));

  global_result.clear();
  istringstream sequence1("1 2 3 4 5");
  OnlineMedian(&sequence1);
  golden = {1, 1.5, 2, 2.5, 3};
  assert(equal(golden.begin(), golden.end(), global_result.begin(),
               global_result.end()));

  global_result.clear();
  istringstream sequence2("1 0 3 5 2 0 1");
  OnlineMedian(&sequence2);
  golden = {1, 0.5, 1, 2, 2, 1.5, 1};
  assert(equal(golden.begin(), golden.end(), global_result.begin(),
               global_result.end()));

  global_result.clear();
  istringstream sequence3("-1");
  OnlineMedian(&sequence3);
  golden = {-1.0};
  assert(equal(golden.begin(), golden.end(), global_result.begin(),
               global_result.end()));
}

int main(int argc, char* argv[]) {
  SimpleTest();

  return 0;
}