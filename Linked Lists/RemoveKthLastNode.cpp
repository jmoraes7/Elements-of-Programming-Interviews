/*
* RemoveKthLastNode.cpp
* -----------------
*
* Chapter 8 Question 8
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

void deleteNode(shared_ptr<ListNode<int> >& node) {
  node->data = node->next->data;
  node->next = node->next->next;
}

void removeKthLast(shared_ptr<ListNode<int> >& head, int k) {
  auto node = head;
  auto tracking = head;
  
  while (k--) {
    node = node->next;
  }
  
  while (node) {
    node = node->next;
    tracking = tracking->next;
  }

  deleteNode(tracking);
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{4, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{3, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{2, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{1, L2});
  
  
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{0, L3});
  shared_ptr<ListNode<int> > L5 = make_shared<ListNode<int> >(ListNode<int>{-1, L4});

  cout << "BEFORE: ";
  PrintList(L5);
  cout << endl;

  cout << "AFTER: ";
  removeKthLast(L5, 2);
  PrintList(L5);
  cout << endl;

  

  // cout << "RESULT: " << node << endl;

  // cout << "Cycle at node with value: " << node->data << endl;
}

int main()
{  
  SimpleTest();

  return 0;
}