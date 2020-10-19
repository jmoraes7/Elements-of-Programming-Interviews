/*
* CircularQueue.cpp
* -----------------
*
* Chapter 9 Question 10
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
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
    explicit Queue(size_t capacity) : entries_(capacity) {}

    void Enqueue(int x) {

      //must resize
      if (num_elements == entries_.size()) {
        rotate(entries_.begin(), entries_.begin() + head_, entries_.end());
        head_ = 0, tail_ = num_elements;
        entries_.resize(entries_.size() * kScaleFactor);
      }

      entries_[tail_] = x;
      tail_ = (tail_ + 1) % entries_.size();
      ++num_elements;
    }

    int Dequeue() {
      if (!num_elements) {
        throw length_error("empty queue");
      }

      --num_elements;
      int ret = entries_[head_];
      head_ = (head_ + 1) % entries_.size();
      return ret;
    }

    size_t size() const { return num_elements; }

  private:
    const int kScaleFactor = 2;
    size_t head_ = 0, tail_ = 0, num_elements = 0;
    vector<int> entries_;
};

void Test() {
  Queue q(8);
  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);
  q.Enqueue(4);
  q.Enqueue(5);
  q.Enqueue(6);
  q.Enqueue(7);
  q.Enqueue(8);
  // Now head = 0 and tail = 0

  assert(1 == q.Dequeue());
  assert(2 == q.Dequeue());
  assert(3 == q.Dequeue());
  // Now head = 3 and tail = 0

  q.Enqueue(11);
  q.Enqueue(12);
  q.Enqueue(13);
  // Ok till here. Now head = 3 and tail = 3

  q.Enqueue(14);  // now the vector (data) is resized; but the head and tail.
  // (or elements) does not change accordingly.
  q.Enqueue(15);
  q.Enqueue(16);
  q.Enqueue(17);
  q.Enqueue(18);
  // The elements starting from head=3 are over-written!

  assert(4 == q.Dequeue());
  assert(5 == q.Dequeue());
  assert(6 == q.Dequeue());
  assert(7 == q.Dequeue());
  assert(8 == q.Dequeue());
  assert(11 == q.Dequeue());
  assert(12 == q.Dequeue());
}

int main(int argc, char* argv[])
{  
  Test();
  Queue q(8);
  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);
  assert(1 == q.Dequeue());
  q.Enqueue(4);
  assert(2 == q.Dequeue());
  assert(3 == q.Dequeue());
  assert(4 == q.Dequeue());
  
  //empty queue
  try {
    q.Dequeue();
  } catch (const exception& e) {
    cout << e.what() << endl;
  }

  // test resize().
  q.Enqueue(4);
  q.Enqueue(4);
  q.Enqueue(4);
  q.Enqueue(4);
  q.Enqueue(4);
  q.Enqueue(4);
  q.Enqueue(4);
  q.Enqueue(4);
  q.Enqueue(4);
  assert(q.size() == 9);
  return 0;
}