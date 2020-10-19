#ifndef STACK_WITH_MAX_H_
#define STACK_WITH_MAX_H_

#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>

using namespace std;

using std::length_error;
using std::max;
using std::stack;

class Stack {
  public:
    bool Empty() const { return element_.empty(); }

    int Max() const {
      if (Empty()) {
        throw length_error("Max(): empty stack");
      }

      return element_with_cached_max_.top().element;
    }

    int Pop() {
      if (Empty()) {
        throw length_error("Pop(): empty stack");
      }

      int element = element_.top();
      element_.pop();

      int max = element_with_cached_max_.top().element;

      if (element == max) {
        element_with_cached_max_.top().count--;

        if (element_with_cached_max_.top().count == 0) {
          element_with_cached_max_.pop();
        }
      }  
      
      return element;
    }

    void Push(int x) {
      element_.push(x);

      if (element_with_cached_max_.empty()) {
        element_with_cached_max_.push(ElementWithCachedMax{x, 1});
      } else {
        int max = element_with_cached_max_.top().element;

        if (x == max) {
          int& count = element_with_cached_max_.top().count;
          ++count;
        } else if (x > max) {
          element_with_cached_max_.push(ElementWithCachedMax{x, 1});
        }
      }
    }

  private:
    struct ElementWithCachedMax {
      int element, count;
    };

    stack<int> element_;
    stack<ElementWithCachedMax> element_with_cached_max_;
};

#endif
