/*
* DeleteNode.cpp
* -----------------
*
* Chapter 8 Question 7
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

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{4, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{3, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{2, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{1, L2});

  cout << "BEFORE: ";
  PrintList(L3);
  cout << endl;

  cout << "AFTER: ";
  deleteNode(L1);
  PrintList(L3);
  cout << endl;
}

int main()
{  
  SimpleTest();

  return 0;
}