/*
* TestForCyclicity.cpp
* -----------------
*
* Chapter 8 Question 4
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

shared_ptr<ListNode<int> > hasCycle(shared_ptr<ListNode<int> > head) {

  shared_ptr<ListNode<int> > fast = head, slow = head;

  while (fast && fast->next && fast->next->next) {
    slow = slow->next, fast = fast->next->next;

    if (fast == slow) {
      //calculate cycle length
      int cycleLen = 0;
      do {
        fast = fast->next;
        cycleLen++;
      } while (fast != slow);

      shared_ptr<ListNode<int> > cycle_advanced_node = head;
      while (cycleLen--) {
        cycle_advanced_node = cycle_advanced_node->next;
      }

      while (cycle_advanced_node != head) {
        cycle_advanced_node = cycle_advanced_node->next;
        head = head->next;
      }
      return head;
    } 
  }
  return nullptr; // No cycle
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{4, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{3, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{2, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{1, L2});
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{0, L3});
  shared_ptr<ListNode<int> > L5 = make_shared<ListNode<int> >(ListNode<int>{-1, L4});

  L0->next = L0;

  auto node = hasCycle(L5);

  cout << "RESULT: " << node << endl;

  cout << "Cycle at node with value: " << node->data << endl;
}

int main()
{  
  SimpleTest();

  return 0;
}