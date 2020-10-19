/*
* CopyPostingsList.cpp
* -----------------
*
* Chapter 22 Question 11
*/

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "../Stacks and Queues/JumpLinkedListNode.h"

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::shared_ptr;
using std::stoi;

shared_ptr<PostingListNode> CopyPostingsList(shared_ptr<PostingListNode> node) {
  if (!node) return nullptr;

  // a -> b -> c -> d
  // a' -> b' -> c' -> d'
  auto curr = node;
  while (curr) {
    shared_ptr<PostingListNode> copy = make_shared<PostingListNode>(PostingListNode{curr->order, curr->next, nullptr});
    curr->next = copy;
    curr = curr->next->next;
  }

  auto jump_iter = node;
  while (jump_iter) {
    if (jump_iter->next) {
      jump_iter->next->jump = jump_iter->jump->next;
    }
    jump_iter = jump_iter->next->next;
  }

  auto iter = node, new_list_head = iter->next;
  while (iter->next) {
    auto temp = iter->next;
    iter->next = iter->next->next;
    iter = temp;
  }

  return new_list_head;
}

void SetPostingsListOrderHelper(shared_ptr<PostingListNode>& node, int* order) {
  
  if (node && node->order == -1) {
    node->order = (*order)++;
    SetPostingsListOrderHelper(node->jump, order);
    SetPostingsListOrderHelper(node->next, order);
  }
}

void SetPostingsListOrder(shared_ptr<PostingListNode>& head) {
  if (head) {
    int order = 1;
    SetPostingsListOrderHelper(head, &order);
  }
}

void PrintList(shared_ptr<PostingListNode> L) {
  while (L) {
    cout << L->order << endl;
    L = L->next;
  }
}

int main(int argc, char** argv) {   
  
  shared_ptr<PostingListNode> L = make_shared<PostingListNode>(PostingListNode{-1, nullptr});
  shared_ptr<PostingListNode> L1 = make_shared<PostingListNode>(PostingListNode{-1, nullptr});
  shared_ptr<PostingListNode> L2 = make_shared<PostingListNode>(PostingListNode{-1, nullptr});
  shared_ptr<PostingListNode> L3 = make_shared<PostingListNode>(PostingListNode{-1, nullptr});

  L->jump = L2;
  L->next = L1;

  L1->jump = L3;
  L1->next = L2;

  L2->jump = L1;
  L2->next = L3;

  L3->jump = L3;
  L3->next = nullptr;
  
  PrintList(L);
  cout << endl;
  SetPostingsListOrder(L);
  PrintList(L);

  cout << endl << "Copied List:" << endl;
  auto copy = CopyPostingsList(L);
  PrintList(copy);
  
  return 0;
}


