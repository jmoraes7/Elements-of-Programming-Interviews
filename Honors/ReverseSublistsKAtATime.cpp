/*
* ReverseSublistsKAtATime.cpp
* -----------------
*
* Chapter 22 Question 9
*/

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "../Linked Lists/Linked_List_Prototype.h"

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::shared_ptr;
using std::stoi;

shared_ptr<ListNode<int> > ReverseListRecursiveHelper(shared_ptr<ListNode<int> > prev,
                                shared_ptr<ListNode<int> > curr) {
  
  auto next = curr->next;
  curr->next = prev;

  if (next) {
    auto res = ReverseListRecursiveHelper(curr, next);
    return res;
  }

  return curr;
}

shared_ptr<ListNode<int> > ReverseListRecursive(shared_ptr<ListNode<int> > L) {
  if (!L || !L->next) {
    return L;
  }
  
  return ReverseListRecursiveHelper(nullptr, L);
} 

shared_ptr<ListNode<int> > ReverseList(shared_ptr<ListNode<int> > L) {
  shared_ptr<ListNode<int> > curr = L, prev = nullptr;

  while (curr) {
    auto temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
  }

  return prev;
} 

shared_ptr<ListNode<int> > ReverseKSublists(shared_ptr<ListNode<int> > L, int k) {
  shared_ptr<ListNode<int> > dummy_head = make_shared<ListNode<int> >(ListNode<int>{-1, nullptr});
  shared_ptr<ListNode<int> > prev_tail = dummy_head;
  shared_ptr<ListNode<int> > sublist_head = L, sublist_tail = L;

  while (sublist_head->next) {
    int sublist_count = k - 1;
    while (sublist_head->next && sublist_count > 0 ) {
      sublist_head = sublist_head->next;
      sublist_count--;
    }

    auto next_tail = sublist_head->next;
    sublist_head->next = nullptr;

    ReverseList(sublist_tail);
    prev_tail->next = sublist_head;
    prev_tail = sublist_tail;
    
    sublist_tail->next = next_tail;
    sublist_tail = sublist_tail->next;
    sublist_head = sublist_tail;

    if (sublist_count > 0) {
      break;
    }

    sublist_count = k - 1;
  }
 
  return dummy_head->next;
}

void PrintListNodes(shared_ptr<ListNode<int> > L) {

  while (L) {
    cout << L->data << endl;
    L = L->next;
  }
}

int main(int argc, char** argv) {   
  
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             2, make_shared<ListNode<int>>(ListNode<int>{
                    3, make_shared<ListNode<int>>(ListNode<int>{
                           4, make_shared<ListNode<int>>(
                                  ListNode<int>{5, nullptr})})})})});

  shared_ptr<ListNode<int> >L2 = make_shared<ListNode<int>>(ListNode<int>{
      1, make_shared<ListNode<int>>(ListNode<int>{
             2, nullptr})});

  PrintListNodes(L);
  cout << endl;

  PrintListNodes(ReverseKSublists(L, 4));
  
  return 0;
}


