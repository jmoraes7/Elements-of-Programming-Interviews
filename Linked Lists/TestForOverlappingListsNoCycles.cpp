/*
* TestForOverlappingListsNoCycles.cpp
* -----------------
*
* Chapter 8 Question 5
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

shared_ptr<ListNode<int> > hasOverlappingLists(shared_ptr<ListNode<int> > L1, shared_ptr<ListNode<int> > L2) {

  int L1_len = 0;
  int L2_len = 0;

  shared_ptr<ListNode<int> > longer;
  shared_ptr<ListNode<int> > shorter;

  auto temp = L1;
  while (temp) {
    temp = temp->next;
    L1_len++;
  }
  longer = L1;

  temp = L2;
  while (temp) {
    temp = temp->next;
    L2_len++;
  }

  if (L2_len > L1_len) {
    shorter = L1;
    longer = L2;
  } else {
    shorter = L2;
  }

  int k = abs(L2_len - L1_len);
  while (k--) {
    longer = longer->next;
  }

  while (shorter != longer && shorter && longer) {
    shorter = shorter->next;
    longer = longer->next;
  }
 
  return longer;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{4, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{3, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{2, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{1, L2});
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{0, L2});
  //shared_ptr<ListNode<int> > L5 = make_shared<ListNode<int> >(ListNode<int>{-1, L3});

  //L0->next = L0;

  auto node = hasOverlappingLists(L3, L4);

  cout << "RESULT: " << node << endl;

  cout << "Cycle at node with value: " << node->data << endl;
}

int main()
{  
  SimpleTest();

  return 0;
}