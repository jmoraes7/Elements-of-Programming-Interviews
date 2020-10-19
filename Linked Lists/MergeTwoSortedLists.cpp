/*
* MergeTwoSortedLists.cpp
* -----------------
*
* Chapter 8 Question 1
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;
 
shared_ptr<ListNode<int> > mergeTwoSortedLists(shared_ptr<ListNode<int> > L1, shared_ptr<ListNode<int> > L2) {
  shared_ptr<ListNode<int> > dummy_head(new ListNode<int>);
  auto tail = dummy_head;

  while (L1 && L2) {
    AppendNode(L1->data <= L2->data ? &L1 : &L2, &tail);
  }

  tail->next = L1 ? L1 : L2;
  
  return dummy_head->next;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L1 = nullptr;
  shared_ptr<ListNode<int> > L2 = nullptr;
  auto result = mergeTwoSortedLists(L1, L2);
  assert(result == nullptr);

  //TEST 2
  L1 = make_shared<ListNode<int> >(ListNode<int>{123, nullptr});
  result = mergeTwoSortedLists(L1, L2);
  assert(result->data == 123);
  
  cout << "TEST 2 result: ";
  PrintList(result);
  cout << endl;

  //TEST 3
  L2 = L1;
  L1 = nullptr;
  result = mergeTwoSortedLists(L1, L2);
  assert(result->data == 123);

  L1 = make_shared<ListNode<int> >(ListNode<int>{100, nullptr});
  L2 = make_shared<ListNode<int> >(ListNode<int>{123, nullptr});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{-123, L1});

  result = mergeTwoSortedLists(L3, L2);
  //assert(result->data == -123 && result->next->data == 123 && result->next->next == nullptr);

  cout << "TEST 3 result: ";
  PrintList(result);
}

int main()
{  
  std::string encoded = "4a1b3c2a";
  std::string decoded = "aaaabcccaa";

  SimpleTest();

  return 0;
}