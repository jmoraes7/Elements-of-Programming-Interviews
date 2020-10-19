/*
* AddListBasedIntegers.cpp
* -----------------
*
* Chapter 8 Question 14
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./Linked_list_Prototype.h"

using namespace std;

shared_ptr<ListNode<int> > addNumbers(shared_ptr<ListNode<int> > L1, shared_ptr<ListNode<int> > L2) {

  shared_ptr<ListNode<int> > dummy_head(new ListNode<int>);
  auto sum_list = dummy_head;

  int carry = 0;
  while (L1 || L2) {
    int sum = carry;

    if (L1) {
      sum += L1->data;
      L1 = L1->next;
    }

    if (L2) {
      sum += L2->data;
      L2 = L2->next;
    }

    sum_list->next = make_shared<ListNode<int>>(ListNode<int>{sum % 10, nullptr});

    carry = sum / 10, sum_list = sum_list = sum_list->next;
  }

  if (carry) {
    sum_list->next = make_shared<ListNode<int>>(ListNode<int>{carry, nullptr});
  }
  
  return dummy_head->next;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{4, nullptr});
  shared_ptr<ListNode<int> > L1 = make_shared<ListNode<int> >(ListNode<int>{1, L0});
  shared_ptr<ListNode<int> > num1 = make_shared<ListNode<int> >(ListNode<int>{3, L1});
  
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{9, nullptr});
  shared_ptr<ListNode<int> > L4 = make_shared<ListNode<int> >(ListNode<int>{0, L3});
  shared_ptr<ListNode<int> > num2 = make_shared<ListNode<int> >(ListNode<int>{7, L4});


  cout << "BEFORE: ";
  PrintList(num1);
  PrintList(num2);
  cout << endl;

  cout << "AFTER: ";
  shared_ptr<ListNode<int> > sum = addNumbers(num1, num2);
  PrintList(sum);

  

}

int main()
{  
  SimpleTest();

  return 0;
}