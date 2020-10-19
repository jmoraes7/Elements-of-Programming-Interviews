/*
* OrderPostingsLIst.cpp
* -----------------
*
* Chapter 9 Question 6
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>

#include "./JumpLinkedListNode.h"

using namespace std;

using std::length_error;
using std::max;
using std::stack;

void SetJumpOrderHelper(const shared_ptr<PostingListNode>& L, int& order) {
  if (L && L->order == -1) {
    L->order = order++;
    SetJumpOrderHelper(L->jump, order);
    SetJumpOrderHelper(L->next, order);
  }
}

void SetJumpOrderRecursive(const shared_ptr<PostingListNode>& L) {
  int order = 0; 
  SetJumpOrderHelper(L, order);
}

void SetJumpOrderIterative(const shared_ptr<PostingListNode>& L) {
  stack<shared_ptr<PostingListNode>> nodes;
  nodes.push(L);
  int order = 0;

  while (!nodes.empty()) {
    auto curr = nodes.top();
    nodes.pop();

    if (curr && curr->order == -1) {
      curr->order = order++;

      nodes.push(curr->next);
      nodes.push(curr->jump);
    }
  }
}

int main()
{  
  shared_ptr<PostingListNode> L = nullptr, curr;
  curr = L;
  // Build a linked list L->1->2->3->4->5->nullptr.
  for (size_t i = 0; i < 5; ++i) {
    shared_ptr<PostingListNode> temp =
        make_shared<PostingListNode>(PostingListNode{-1, nullptr, nullptr});
    if (curr) {
      curr->next = temp;
      curr = temp;
    } else {
      curr = L = temp;
    }
  }

  L->jump = nullptr;  // no jump from 1
  L->next->jump = L->next->next->next;  // 2's jump points to 4
  L->next->next->jump = L;  // 3's jump points to 1
  L->next->next->next->jump = nullptr;  // no jump from 4
  L->next->next->next->next->jump =
      L->next->next->next->next;  // 5's jump points to 5
  shared_ptr<PostingListNode> temp = L;
  
  //SetJumpOrderRecursive(L);
  SetJumpOrderIterative(L);

  while (temp) {
    cout << temp->order << endl;
    temp = temp->next;
  }

  return 0;
}