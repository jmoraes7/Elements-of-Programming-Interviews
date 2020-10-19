/*
* RemoveDuplicates.cpp
* -----------------
*
* Chapter 8 Question 9
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

void removeDuplicates(shared_ptr<ListNode<int> >& head) {
  auto node = head;

  while (node) {
    auto temp = node->next;

    while (temp && node->data == temp->data) {
      temp = temp->next;
      node->next = temp;
    }

    node = node->next;
  }

}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{11, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{11, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{7, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{5, L2});
  
  
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{3, L3});
  shared_ptr<ListNode<int> > L5 = make_shared<ListNode<int> >(ListNode<int>{2, L4});
  shared_ptr<ListNode<int> > L6 = make_shared<ListNode<int> >(ListNode<int>{2, L5});
  shared_ptr<ListNode<int> > L7 = make_shared<ListNode<int> >(ListNode<int>{2, L6});


  cout << "BEFORE: ";
  PrintList(L7);
  cout << endl;

  cout << "AFTER: ";
  removeDuplicates(L7);
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