/*
* QueueViaStacks.cpp
* -----------------
*
* Chapter 9 Question 11
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
    void Enqueue(int x) { Q1_.push(x); }
  
    int Dequeue() {
      if (Q2_.empty()) {
        
        while (!Q1_.empty()) {
          Q2_.push(Q1_.top());
          Q1_.pop();
        }

      }

      if (Q2_.empty()) {
        throw length_error("Queue is empty");
      }

      int ret = Q2_.top();
      Q2_.pop();

      return ret;
    }

  private:
    stack<int> Q1_, Q2_;
    
};

int main(int argc, char* argv[])
{  
  Queue Q;
  Q.Enqueue(1);
  Q.Enqueue(2);
  assert(1 == Q.Dequeue());
  assert(2 == Q.Dequeue());
  Q.Enqueue(3);
  assert(3 == Q.Dequeue());
  try {
    Q.Dequeue();
    assert(false);
  } catch (const exception& e) {
    cout << e.what() << endl;
  }
  Q.Enqueue(-1);
  Q.Enqueue(123);
  Q.Enqueue(numeric_limits<int>::max());
  Q.Enqueue(numeric_limits<int>::min());
  Q.Enqueue(0);
  assert(-1 == Q.Dequeue());
  Q.Enqueue(0);
  assert(123 == Q.Dequeue());
  assert(numeric_limits<int>::max() == Q.Dequeue());
  assert(numeric_limits<int>::min() == Q.Dequeue());
  assert(0 == Q.Dequeue());
  assert(0 == Q.Dequeue());
  try {
    Q.Dequeue();
    assert(false);
  } catch (const exception& e) {
    cout << e.what() << endl;
  }
  return 0;
}