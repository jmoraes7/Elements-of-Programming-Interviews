/*
* SortingAlgoForLists.cpp
* -----------------
*
* Chapter 14 Question 10
*/

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include "../Linked Lists/Linked_list_prototype.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

void insertionSort(vector<int>& arr) {
  for (int i = 0; i < arr.size(); ++i) {
    int j = i;
    while (j > 0 && (arr[j] < arr[j-1])) {
      std::swap(arr[j], arr[j-1]);
    }
  }
}

shared_ptr<ListNode<int> > MergeTwoSortedLists(shared_ptr<ListNode<int> >& A, shared_ptr<ListNode<int> >& B) {
  shared_ptr<ListNode<int> > dummy_head = make_shared<ListNode<int> >(ListNode<int>{0, nullptr});
  auto tail = dummy_head;

  while (A && B) {
    if (A->data < B->data) {
      tail->next = A;
      A = A->next;
    } else {
      tail->next = B;
      B = B->next;
    }

    tail = tail->next;
  }

  tail->next = A ? A : B;

  return dummy_head->next;
}

shared_ptr<ListNode<int> > StableSortList(shared_ptr<ListNode<int> >& L) {
  if (L == nullptr || L->next == nullptr) {
    return L;
  }
  auto slow = L, fast = slow->next;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  auto L2 = slow->next;
  slow->next = nullptr;

  auto sublist_1 = StableSortList(L);
  auto sublist_2 = StableSortList(L2);
   
  return MergeTwoSortedLists(sublist_1, sublist_2);
}

shared_ptr<ListNode<int> > InsertionSort(const shared_ptr<ListNode<int> >& L) {
  shared_ptr<ListNode<int> > dummy_head = make_shared<ListNode<int> >(ListNode<int>{0, L});
  auto iter = L;

  while (iter->next) {
    if (iter->data > iter->next->data) {
      auto target = iter->next, prev = dummy_head;

      while (prev->next->data < target->data) {
        prev = prev->next;
      }

      auto temp = prev->next;
      prev->next = target;
      iter->next = target->next;
      target->next = temp;

    } else {
      iter = iter->next;
    }
  }

  return dummy_head->next; 
}

shared_ptr<ListNode<int> > SelectionSort(const shared_ptr<ListNode<int> >& L) {
  
  shared_ptr<ListNode<int> > dummy_head = make_shared<ListNode<int> >(ListNode<int>{0, L});
  auto iter = dummy_head;
  int count = 0;
  while (iter->next) {
    auto curr_min_prev = iter;
    auto min_iter = iter;

    //get min node in unsorted sublist
    while (min_iter->next) {
      if (min_iter->next->data < curr_min_prev->next->data) {
        curr_min_prev = min_iter;
      }
      min_iter = min_iter->next;
    }
    
    auto min_node = curr_min_prev->next;
    curr_min_prev->next = curr_min_prev->next->next;

    min_node->next = iter->next;
    iter->next = min_node;
    iter = iter->next;

    count++;
    if (count == 15) {
      break;
    }
  }

  return dummy_head->next;
}

void SimpleTest() {
  shared_ptr<ListNode<int> > L1 = nullptr;
  shared_ptr<ListNode<int> > L2 = nullptr;
  auto result = MergeTwoSortedLists(L1, L2);
  assert(result == nullptr);

  //TEST 2
  L1 = make_shared<ListNode<int> >(ListNode<int>{123, nullptr});
  result = MergeTwoSortedLists(L1, L2);
  assert(result->data == 123);
  
  cout << "TEST 2 result: ";
  PrintList(result);
  cout << endl;

  //TEST 3
  L2 = L1;
  L1 = nullptr;
  result = MergeTwoSortedLists(L1, L2);
  assert(result->data == 123);

  shared_ptr<ListNode<int> > L0 = make_shared<ListNode<int> >(ListNode<int>{300, nullptr});

  L1 = make_shared<ListNode<int> >(ListNode<int>{100, nullptr});
  L2 = make_shared<ListNode<int> >(ListNode<int>{123, L0});
  shared_ptr<ListNode<int> > L3 = make_shared<ListNode<int> >(ListNode<int>{-123, L1});

  result = MergeTwoSortedLists(L3, L2);
  //assert(result->data == -123 && result->next->data == 123 && result->next->next == nullptr);

  cout << "TEST 3 result: ";
  PrintList(result);
  cout << endl;
}

int main(int argc, char** argv) {
  SimpleTest();
  
  vector<int> arr{ 4, 0, -1, 3, 7, 5};

  insertionSort(arr);

  for (int x : arr) {
    cout << x << " ";
  }
  cout << endl << endl;
  
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
        1, make_shared<ListNode<int>>(ListNode<int>{
             4, make_shared<ListNode<int>>(ListNode<int>{
                    3, make_shared<ListNode<int>>(ListNode<int>{
                           2, make_shared<ListNode<int>>(
                                  ListNode<int>{5, nullptr})})})})});
  
  
  
  auto result = StableSortList(L);
  shared_ptr<ListNode<int>> pre = nullptr;
  while (result) {
    assert(!pre || pre->data <= result->data);
    pre = result;
    cout << result->data << endl;
    result = result->next;
  }

  return 0;
}
