/*
* TestForOverlappingListsWithCycles.cpp
* -----------------
*
* Chapter 8 Question 6
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

shared_ptr<ListNode<int> > hasOverlappingListsNoCycle(shared_ptr<ListNode<int> > L1, shared_ptr<ListNode<int> > L2) {

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

int distance(shared_ptr<ListNode<int> > a, shared_ptr<ListNode<int> > b) {
  int dist = 0;

  while (a != b) {
    a = a->next; ++dist;
  }

  return dist;
}

shared_ptr<ListNode<int> > hasOverlappingLists(shared_ptr<ListNode<int> > L1, shared_ptr<ListNode<int> > L2) {

  int L1_len = 0;
  int L2_len = 0;

  shared_ptr<ListNode<int> > longer;
  shared_ptr<ListNode<int> > shorter;

  auto root1 = hasCycle(L1), root2 = hasCycle(L2);

  if (!root1 && !root2) {
    return hasOverlappingListsNoCycle(L1, L2);
  } else if ((!root1 && root2) || (root1 && !root2)) {
    return nullptr;
  }

  //Both lists have cycles
  auto temp = root2;
  do {
    temp = temp->next;
  } while(temp != root1 && temp != root2);

  //L1 and L2 do not end in the same cycle
  if (temp != root1) {
    return nullptr; //Cycles are disjoint
  }

  int stem1_length = distance(L1, root1), stem2_length = distance(L2, root2);
  int diff = abs(stem1_length - stem2_length);
  while (diff--) {
    if (stem1_length > stem2_length) {
      L1 = L1->next;
    } else {
      L2 = L2->next;
    }
  }

  while (L1 != L2 && L1 != root1 && L2 != root2) {
    L1 = L1->next; L2 = L2->next;
  }

  return L1 == L2 ? L1 : root1;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{4, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{3, L0});
  shared_ptr<ListNode<int> > L2 = make_shared<ListNode<int> >(ListNode<int>{2, L1});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{1, L2});
  
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{0, L2});

  //L4 -> L1 -> L0 -> L2
  
  //L3 -> L2 -> L1 -> L0 -> L2

  L0->next = L2;

  auto node = hasOverlappingLists(L3, L4);

  cout << "Cycle at node with value: " << node->data << endl;
}

int main()
{  
  SimpleTest();

  return 0;
}