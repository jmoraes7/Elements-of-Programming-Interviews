#ifndef DOUBLY_LINKED_LIST_PROTOTYPE_H_
#define DOUBLY_LINKED_LIST_PROTOTYPE_H_

#include <memory>
#include <iostream> 

using namespace std;

using std::shared_ptr;

template <typename T>
struct ListNode {
  T data;
  shared_ptr<ListNode<T> > prev, next;
};

#endif
