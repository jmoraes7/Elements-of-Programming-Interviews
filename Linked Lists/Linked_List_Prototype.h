#ifndef LINKED_LIST_PROTOTYPE_H_
#define LINKED_LIST_PROTOTYPE_H_

#include <memory>
#include <iostream> 

using namespace std;

using std::shared_ptr;

// @include
template <typename T>
struct ListNode {
  T data;
  shared_ptr<ListNode<T>> next;
};
// @exclude

void PrintList(shared_ptr<ListNode<int> > node) {
  while (node) {
    cout << node->data << " -> ";
    node = node->next;
  }

  cout << endl;
}

void AppendNode(shared_ptr<ListNode<int> > *node,
                shared_ptr<ListNode<int> > *tail) {
  (*tail)->next = *node;
  *tail = *node;  // Updates tail.
  *node = (*node)->next;
}

#endif
