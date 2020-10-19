/*
* QueueWithMaxAPI.cpp
* -----------------
*
* Chapter 9 Question 12
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <stdexcept>
#include <utility>
#include <random>

#include "./StackWithMaxAPI.h"

using namespace std;

using std::cout;
using std::default_random_engine;
using std::endl;
using std::istringstream;
using std::random_device;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

class Queue {
  public: 
    void Enqueue(int x) {
      while (!candidate_max_elems.empty() && candidate_max_elems.back() < x) {
        candidate_max_elems.pop_back();
      }
      candidate_max_elems.push_back(x);
      entries.push(x);
    }
  
    int Dequeue() {
      if (!entries.empty()) {
        int ret = entries.front();
        entries.pop();

        if (ret == candidate_max_elems.front()) { 
          candidate_max_elems.pop_front();
        }

        return ret;
      }
      throw length_error("Queue is empty"); 
    } 
  
    int Max() {
      if (!candidate_max_elems.empty()) {
        return candidate_max_elems.front();
      }

      throw length_error("Queue is empty");
    }

  private:
    queue<int> entries;
    deque<int> candidate_max_elems;
    
};

class FastQueue {
  public: 
    void Enqueue(int x) { enqueue_.Push(x); }
  
    int Dequeue() {
      if (dequeue_.Empty()) {
        while(!enqueue_.Empty()) {
          dequeue_.Push(enqueue_.Pop());
        }
      }

      if (!dequeue_.Empty()) {
        return dequeue_.Pop();
      }

      throw length_error("Queue is empty");
    } 
  
    int Max() {
      if (!enqueue_.Empty()) {
        
        return dequeue_.Empty() ? 
          enqueue_.Max() :
          max(enqueue_.Max(), dequeue_.Max());
      }

      if (!dequeue_.Empty()) {
        return dequeue_.Max();
      }

      throw length_error("Queue is empty");
    }

  private:
    Stack enqueue_;
    Stack dequeue_;
    
};

void SimpleTest() {
  FastQueue Q;
  Q.Enqueue(11);
  Q.Enqueue(2);
  assert(11 == Q.Max());
  assert(11 == Q.Dequeue());
  assert(2 == Q.Max());
  assert(2 == Q.Dequeue());
  Q.Enqueue(3);
  assert(3 == Q.Max());
  assert(3 == Q.Dequeue());
  Q.Enqueue(numeric_limits<int>::max() - 1);
  Q.Enqueue(numeric_limits<int>::max());
  Q.Enqueue(-2);
  Q.Enqueue(-1);
  Q.Enqueue(-1);
  Q.Enqueue(numeric_limits<int>::min());
  assert(numeric_limits<int>::max() == Q.Max());
  assert(numeric_limits<int>::max() - 1 == Q.Dequeue());
  assert(numeric_limits<int>::max() == Q.Max());
  assert(numeric_limits<int>::max() == Q.Dequeue());
  assert(-1 == Q.Max());
  assert(-2 == Q.Dequeue());
  assert(-1 == Q.Max());
  assert(-1 == Q.Dequeue());
  assert(-1 == Q.Dequeue());
  assert(numeric_limits<int>::min() == Q.Max());
  assert(numeric_limits<int>::min() == Q.Dequeue());
  try {
    cout << "Q is empty, Max() call should except = " << Q.Max();
    assert(false);
  } catch (const exception& e) {
    cout << e.what() << endl;
  }
}

// Just for testing.
int main(int argc, char* argv[]) {
  SimpleTest();
  FastQueue Q;
  Q.Enqueue(1);
  Q.Enqueue(2);
  assert(2 == Q.Max());
  assert(1 == Q.Dequeue());  // 1
  assert(2 == Q.Max());
  assert(2 == Q.Dequeue());  // 2
  Q.Enqueue(3);
  assert(3 == Q.Max());
  assert(3 == Q.Dequeue());  // 3
  try {
    Q.Max();
    assert(false);
  } catch (const exception& e) {
    cout << e.what() << endl;  // throw
  }
  try {
    Q.Dequeue();
    assert(true);
  } catch (const exception& e) {
    cout << e.what() << endl;  // throw
  }
  return 0;
}