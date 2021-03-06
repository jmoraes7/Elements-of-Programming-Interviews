/*
* BSTToDoublyLinkedList.cpp
* -----------------
*
* Chapter 22 Question 27
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "./DoublyLinkedList.h"

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::greater;
using std::hash;
using std::istringstream;
using std::length_error;
using std::make_unique;
using std::unique_ptr;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::stoi;
using std::unordered_map;
using std::unordered_set;
using std::vector;

std::pair<shared_ptr<ListNode<int> >, shared_ptr<ListNode<int> > > BuildDoublyLinkedListHelper(shared_ptr<ListNode<int> > tree) {
  if (!tree) {
    return {nullptr, nullptr};
  }

  // cout << tree->data << endl;//" " << tree->prev->data << " " << tree->next->data << endl;


  auto left = BuildDoublyLinkedListHelper(tree->prev);
  auto right = BuildDoublyLinkedListHelper(tree->next);
  
  // if (tree->data == 1) {
  //   cout << "TRACER: " << left.first->data << " " << left.second->data << endl;
  // }
  // cout << "AFTER :" << endl;
  
  
  tree->prev = left.second;
  if (left.second) {
    left.second->next = tree;
  }

  tree->next = right.first;
  if (right.first) {
    right.first->prev = tree;
  }

  shared_ptr<ListNode<int> > sublist_head = left.first ? left.first : tree;
  shared_ptr<ListNode<int> > sublist_tail = right.second ? right.second : tree;

  return { sublist_head, sublist_tail };
}

shared_ptr<ListNode<int> > BuildDoublyLinkedListFromBST(shared_ptr<ListNode<int> > tree) {
  auto L = BuildDoublyLinkedListHelper(tree).first;
  return L;
}

shared_ptr<ListNode<int> > BuildBSTHelper(
  shared_ptr<ListNode<int> > L, int start, int end) {
  if (start >= end) return nullptr;

  int dist_to_mid = ((end - start) / 2);

  auto curr = L;
  for (int i = 0; i < dist_to_mid; i++) {
    curr = curr->next;
  } 

  //cout << start << " " << end << " Mid: " << curr->data << endl;
  curr->prev = BuildBSTHelper(L, start, start + dist_to_mid);
  curr->next = BuildBSTHelper(curr->next, start + dist_to_mid + 1, end);
  
  return curr;
} 

shared_ptr<ListNode<int> > BuildBSTFromSortedDoublyLinkedList(
    shared_ptr<ListNode<int> > L, int length) {
   return BuildBSTHelper(L, 0, length);
}

void InOrderTraversal(shared_ptr<ListNode<int> > root, int depth) {
  if (root && depth < 5) {
    InOrderTraversal(root->prev, depth + 1);
    cout << root->data << " - Depth: " << depth << endl;
    InOrderTraversal(root->next, depth + 1);
  }
}

int main(int argc, char** argv) {   
  
  shared_ptr<ListNode<int> > temp0 =
      make_shared<ListNode<int> >(ListNode<int>{0});
  shared_ptr<ListNode<int> > temp1 =
      make_shared<ListNode<int> >(ListNode<int>{1});
  shared_ptr<ListNode<int> > temp2 =
      make_shared<ListNode<int> >(ListNode<int>{2});
  shared_ptr<ListNode<int> > temp3 =
      make_shared<ListNode<int>>(ListNode<int>{3});
  shared_ptr<ListNode<int> > temp4 =
      make_shared<ListNode<int> >(ListNode<int>{4});
  shared_ptr<ListNode<int> > temp5 =
      make_shared<ListNode<int> >(ListNode<int>{5});
  shared_ptr<ListNode<int> > temp6 =
    make_shared<ListNode<int> >(ListNode<int>{6});
  shared_ptr<ListNode<int> > temp7 =
    make_shared<ListNode<int> >(ListNode<int>{7});
  shared_ptr<ListNode<int> > temp8 =
    make_shared<ListNode<int> >(ListNode<int>{8});
  
  temp0->next = temp1;
  temp1->next = temp2;
  temp2->next = temp3;
  temp3->next = temp4;
  temp4->next = temp5;
  temp5->next = temp6;
  temp6->next = temp7;
  temp7->next = temp8;
  temp8->next = nullptr;
  
  temp0->prev = nullptr;
  temp1->prev = temp0;
  temp2->prev = temp1;
  temp3->prev = temp2;
  temp4->prev = temp3;
  temp5->prev = temp4;
  temp6->prev = temp5;
  temp7->prev = temp6;
  temp8->prev = temp7;

  auto BST = BuildBSTFromSortedDoublyLinkedList(temp0, 9);
  InOrderTraversal(BST, 1);

  auto linked_list = BuildDoublyLinkedListFromBST(BST);

  while (linked_list) {
    cout << "HERE: " << linked_list->data << endl;
    linked_list = linked_list->next;
  }

  return 0;
}


