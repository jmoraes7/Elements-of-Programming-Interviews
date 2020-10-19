/*
* CyclicallyRightShiftList.cpp
* -----------------
*
* Chapter 8 Question 10
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

shared_ptr<ListNode<int> > cyclicalRightShiftByK(shared_ptr<ListNode<int> >& list, int k) {
  if (list == nullptr) return list;

  auto tail = list;
  int len = 1;
  while (tail->next) {
    ++len, tail = tail->next;
  }

  k % len;
  if (k == 0) {
    return list;
  }

  tail->next = list;

  int steps_to_new_head = len - k;
  auto new_tail = tail;

  while(steps_to_new_head--) {
    new_tail = new_tail->next;
  }

  auto new_head = new_tail->next;
  new_tail->next = nullptr;
    
  return new_head;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{11, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{11, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{7, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{5, L2});
  
  
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{3, L3});
  shared_ptr<ListNode<int> > L5 = make_shared<ListNode<int> >(ListNode<int>{2, L4});
  shared_ptr<ListNode<int> > L6 = make_shared<ListNode<int> >(ListNode<int>{2, L5});
  shared_ptr<ListNode<int> > L7 = make_shared<ListNode<int> >(ListNode<int>{1, L6});


  cout << "BEFORE: ";
  PrintList(L7);
  cout << endl;

  cout << "AFTER: ";
  L7 = cyclicalRightShiftByK(L7, 1);
  PrintList(L7);
  cout << endl;

  

  // cout << "RESULT: " << node << endl;

  // cout << "Cycle at node with value: " << node->data << endl;
}

int main()
{  
  SimpleTest();

  return 0;
}