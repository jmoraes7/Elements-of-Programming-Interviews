/*
* ReverseSublist.cpp
* -----------------
*
* Chapter 8 Question 3
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

shared_ptr<ListNode<int> > reverseSublistClean(shared_ptr<ListNode<int> > head, int start, int end) {
    if (start == end) {
      return head;
    }

    auto dummy_head = make_shared<ListNode<int> >(ListNode<int>{0, head});

    auto sublist_head = dummy_head;
    int k = 1;
    while (k++ < start) {
      sublist_head = sublist_head->next;
    }

    auto sublist_tail = sublist_head->next;
    while (start++ < end) {
      auto temp = sublist_tail->next;
      sublist_tail->next = temp->next;
      temp->next = sublist_head->next;
      sublist_head->next = temp;
    }

    return dummy_head->next;
}

shared_ptr<ListNode<int> > reverseSublist(shared_ptr<ListNode<int> > head, int start, int end) {
  shared_ptr<ListNode<int> > dummy_head = make_shared<ListNode<int> >(ListNode<int>{0, head});

  shared_ptr<ListNode<int> > before_tail;
  shared_ptr<ListNode<int> > sublist_tail;

  shared_ptr<ListNode<int> > prev = nullptr;
  shared_ptr<ListNode<int> > curr = dummy_head;

  int count = 0;

  while (curr) {
    if (count == start - 1) {
      before_tail = curr;
      sublist_tail = curr->next;
    }

    if (count >= start) {
      auto next = curr->next;
      curr->next = prev;
      prev = curr;

      if (count == end) {
        before_tail->next = curr;
        sublist_tail->next = next;
        
        return dummy_head->next;
      }

      curr = next;
    } else {
      curr = curr->next;
    }
    
    count++;
  }

  return nullptr;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{4, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{3, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{2, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{1, L2});

  cout << "Original List: ";
  PrintList(L3);
  cout << endl;

  cout << "Reversed List: " << endl;
  PrintList(reverseSublistClean(L3, 2, 3));
}

int main()
{  
  SimpleTest();

  return 0;
}