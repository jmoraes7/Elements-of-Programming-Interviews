/*
* ListZipping.cpp
* -----------------
*
* Chapter 22 Question 10
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

shared_ptr<ListNode<int> > ReverseLinkedList(shared_ptr<ListNode<int> > L) {
  if (!L->next) return L;

  auto new_head = ReverseLinkedList(L->next);
  L->next->next = L;
  L->next = nullptr;

  return new_head;
}

shared_ptr<ListNode<int> > ZipList(shared_ptr<ListNode<int> > L) {
  if (!L || !L->next) {
    return L;
  }

  auto slow = L, fast = L;
  while (fast && fast->next && fast->next->next) {
    cout << "SLOW: " << slow->data << " FAST: " << fast->data << endl;
    slow = slow->next, fast = fast->next->next;
  }

  auto first_half_head = L, second_half_head = slow->next;
  slow->next = nullptr;
  
  second_half_head = ReverseLinkedList(second_half_head);

  auto first_half_iter = first_half_head, second_half_iter = second_half_head; 
  while (second_half_iter) {
    auto temp = second_half_iter->next;
    second_half_iter->next = first_half_iter->next;
    first_half_iter->next = second_half_iter;
    first_half_iter = first_half_iter->next->next;
    second_half_iter = temp;
  }

  return first_half_head;
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

  PrintListNodes(ZipList(L));
  
  return 0;
}


