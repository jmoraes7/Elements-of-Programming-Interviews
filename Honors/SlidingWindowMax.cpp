/*
* SlidingWindowMax.cpp
* -----------------
*
* Chapter 22 Question 14
*/

#include <cassert>
#include <deque>
#include <iostream>
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
using std::queue;
using std::shared_ptr;
using std::stoi;
using std::vector;

class QueueWithMax {
  public:
    void Enqueue(double elem) {
      elements.push(elem);

      while (!max_tracker.empty() && max_tracker.back() < elem) {
        max_tracker.pop_back();
      }

      max_tracker.push_back(elem);
    }

    double Dequeue() {
      double elem = elements.front();

      if (elem == max_tracker.front()) {
        max_tracker.pop_front();
      }

      elements.pop();
    }

    double Max() {
      if (!max_tracker.empty()) {
          return max_tracker.front();
      }

      throw length_error("Queue is empty");
    }

    int Size() {
      return elements.size();
    }

  private:
    queue<double> elements;
    deque<double> max_tracker;
};

vector<double> GetSlidingWindowMax(vector<double> arr, int w) {
  
  QueueWithMax queue;
  vector<double> window_maximums;

  for (int i = 0; i < arr.size(); i++) {

    if (queue.Size() == w) {
      queue.Dequeue();
    }

    
    queue.Enqueue(arr[i]);

    window_maximums.push_back(queue.Max());

    cout << queue.Max() << endl;
  }

  return window_maximums;
}

int main(int argc, char** argv) {   
  
  vector<double> A{1.3, 0, 2.5, 3.7, 0, 1.4, 2.6, 0, 2.2, 1.7, 0, 0, 0, 0, 1.7};

  auto results = GetSlidingWindowMax(A, 3);

  for (double x : results) {
    cout << x << " ";
  }
  
  return 0;
}


