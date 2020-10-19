/*
* ListPivoting.cpp
* -----------------
*
* Chapter 8 Question 13
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

shared_ptr<ListNode<int> > pivotList(shared_ptr<ListNode<int> > list, int k) {
  shared_ptr<ListNode<int> > less_head(new ListNode<int>), equal_head(new ListNode<int>), 
                             greater_head(new ListNode<int>);
  
  shared_ptr<ListNode<int> > less_iter = less_head, equal_iter = equal_head, greater_iter = greater_head;

  while (list) {
    if (list->data < k) {
      AppendNode(&list, &less_iter);
    } else if (list->data == k) {
      AppendNode(&list, &equal_iter);
    } else {
      AppendNode(&list, &greater_iter);
    }
  }
  
  if (greater_head->next) {
    equal_iter->next = greater_head->next;
  }

  if (equal_head->next) {
    less_iter->next = equal_head->next;
  }

  return less_head->next;
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
  L7 = pivotList(L7, 1);
  PrintList(L7);

  

}

int main()
{  
  SimpleTest();

  return 0;
}