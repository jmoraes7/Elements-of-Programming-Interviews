/*
* EvenOddMerge.cpp
* -----------------
*
* Chapter 8 Question 11
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;



shared_ptr<ListNode<int> > evenOddMerge(shared_ptr<ListNode<int> >& list) {
  if (!list->next && !list->next->next) { return list; }

  auto head = list;

  shared_ptr <ListNode<int> > odds = nullptr;
  shared_ptr <ListNode<int> > odds_head = nullptr;

  while (list->next) {
    auto next_node = list->next;

    list->next = next_node->next;
    next_node->next = nullptr;

    if (odds) {
      odds->next = next_node;
      odds = odds->next;
    } else {
      odds = next_node;
      odds_head = next_node;
    }

    list = list->next;
  }
  
  list->next = odds_head;
  
  return head;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{8, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{7, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{6, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{5, L2});
  
  
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{4, L3});
  shared_ptr<ListNode<int> > L5 = make_shared<ListNode<int> >(ListNode<int>{3, L4});
  shared_ptr<ListNode<int> > L7 = make_shared<ListNode<int> >(ListNode<int>{2, L5});
  //shared_ptr<ListNode<int> > L7 = make_shared<ListNode<int> >(ListNode<int>{1, L6});


  cout << "BEFORE: ";
  PrintList(L7);
  cout << endl;

  cout << "AFTER: ";
  L7 = evenOddMerge(L7);
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