/*
* ReverseLinkedList.cpp
* -----------------
*
* Chapter 8 Question 2
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

shared_ptr<ListNode<int> > reverseRecursive(shared_ptr<ListNode<int> > head) {
  if (!head->next) {
    return head;
  }

  auto new_head = reverseRecursive(head->next);
  head->next->next = head;
  head->next = nullptr;

  return new_head;
}
shared_ptr<ListNode<int> > reverseSublist(shared_ptr<ListNode<int> > head) {
  shared_ptr<ListNode<int> > prev = nullptr;
  shared_ptr<ListNode<int> > curr = head;

  while (curr) {
    auto next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next; 
  }

  return prev;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{4, nullptr});;
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{3, L0});;
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{2, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{1, L2});

  cout << "Original List: ";
  PrintList(L3);
  cout << endl;

  cout << "Reversed List: " << endl;
  PrintList(reverseSublist(L3));
}

int main()
{  
  SimpleTest();

  return 0;
}