/*
* IsLinkedListAPalindrome.cpp
* -----------------
*
* Chapter 8 Question 12
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

shared_ptr<ListNode<int> > reverseList(shared_ptr<ListNode<int> > list) {
  auto curr = list;
  shared_ptr<ListNode<int> > prev = nullptr;

  while (curr) {
    auto next = curr->next;

    curr->next = prev;
    prev = curr;
    curr = next;
  }

  return prev;
}

bool isPalindrome(shared_ptr<ListNode<int> >& list) {
  
  auto slow = list;
  auto fast = list;

  while (fast && fast->next && fast->next->next) {
    slow = slow->next; 
    fast = fast->next->next;
  }

  shared_ptr<ListNode<int> > second_half_list = reverseList(slow->next);

  while (second_half_list) {
    if (second_half_list->data != list->data) {
      return false;
    }

    list = list->next;
    second_half_list = second_half_list->next;
  }

  return true;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{2, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{3, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{4, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{5, L2});
  
  
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{4, L3});
  shared_ptr<ListNode<int> > L5 = make_shared<ListNode<int> >(ListNode<int>{3, L4});
  shared_ptr<ListNode<int> > L7 = make_shared<ListNode<int> >(ListNode<int>{2, L5});
  //shared_ptr<ListNode<int> > L7 = make_shared<ListNode<int> >(ListNode<int>{1, L6});


  cout << "BEFORE: ";
  PrintList(L7);
  cout << endl;

  cout << "AFTER: ";
  bool result = isPalindrome(L7);
  cout << "IS PALINDROME: " << result << endl;

  

  // cout << "RESULT: " << node << endl;

  // cout << "Cycle at node with value: " << node->data << endl;
}

int main()
{  
  SimpleTest();

  return 0;
}