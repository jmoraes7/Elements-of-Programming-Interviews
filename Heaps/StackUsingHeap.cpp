/*
* StackUsingHeap.cpp
* -----------------
*
* Chapter 11 Question 7
*/

#include <algorithm>
#include <cassert>
#include <functional>
#include <stdexcept>

#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::exception;
using std::greater;
using std::istringstream;
using std::length_error;
using std::less;
using std::numeric_limits;
using std::priority_queue;
using std::random_device;
using std::string;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

struct StackEntry {
  public:
    bool operator<(const StackEntry& that) const {
      return idx < that.idx;
    }

    int idx, val;
};

class Stack { 
  public: 
    void Push(int x) { max_heap.push(StackEntry{idx_++, x}); }
    
    int Pop() {
      if (max_heap.empty()) {
        throw length_error("Stack is empty");
      }

      int val = max_heap.top().val;
      max_heap.pop();

      return val;
    }

        int Peek() { return max_heap.top().val; }



  private:
    int idx_ = 0;
    priority_queue<StackEntry, vector<StackEntry> > max_heap;
};

int main() {
  Stack s;
  s.Push(1);
  s.Push(2);
  s.Push(3);
  assert(s.Peek() == 3);
  s.Pop();
  assert(s.Peek() == 2);
  s.Pop();
  s.Push(4);
  assert(s.Peek() == 4);
  s.Pop();
  s.Pop();
  try {
    s.Pop();
    assert(false);
  } catch (const exception& e) {
    cout << "empty stack" << endl;
    cout << e.what() << endl;
  }

  s.Push(0);
  s.Push(-1);
  s.Push(numeric_limits<int>::max());
  assert(s.Peek() == numeric_limits<int>::max());
  s.Pop();
  assert(s.Peek() == -1);
  s.Pop();
  assert(s.Peek() == 0);
  s.Pop();
  try {
    s.Pop();
    assert(false);
  } catch (const exception& e) {
    cout << "empty stack" << endl;
    cout << e.what() << endl;
  }
  s.Push(0);

  assert(s.Peek() == 0);
  return 0;
}