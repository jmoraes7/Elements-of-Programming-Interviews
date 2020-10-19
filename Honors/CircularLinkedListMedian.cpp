/*
* CircularLinkedListMedian.cpp
* -----------------
*
* Chapter 22 Question 12
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

double GetListMedian(shared_ptr<ListNode<int> >& node) {
  if (!node) return 0;

  auto iter = node;
  while (iter->next->data > iter->data) {
    iter = iter->next;
  }
  auto first_node = iter->next;

  auto fast = first_node, slow = first_node;
  while (fast->next != first_node && fast->next->next != first_node) {
    fast = fast->next->next, slow = slow->next;
  }

  if (fast->next == first_node) { //even # of nodes in list
    return slow->data;
  }

  return 0.5 * (slow->data + slow->next->data) ;
}

int main(int argc, char** argv) {   
  
  shared_ptr<ListNode<int> > L = make_shared<ListNode<int> >(ListNode<int>{17, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{2, nullptr});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{2, nullptr});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{5, nullptr});
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{9, nullptr});
  shared_ptr<ListNode<int> > L5 = make_shared<ListNode<int> >(ListNode<int>{9, nullptr});


  L->next = L1;
  L1->next = L2;
  L2->next = L3;
  L3->next = L4;
  L4->next = L5;
  L5->next = L;


  // 17 2 2 5 9- 9  10
  //        s    f   
  
  cout << endl << GetListMedian(L) << endl;
  
  return 0;
}


