/*
* ReconstructTreeFromPreorderTraversal.cpp
* -----------------
*
* Chapter 10 Question 11
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

#include "./BinaryTreeNodeWithParent.h"

unique_ptr<BinaryTreeNode<int>> ReconstructPreorderHelper(const vector<int*>&,
                                                          int*);

unique_ptr<BinaryTreeNode<int> > ReconstructPreorder(const vector<int*>& preorder) {
  int idx_pointer = 0; 
  return ReconstructPreorderHelper(preorder, &idx_pointer);
}

unique_ptr<BinaryTreeNode<int> > ReconstructPreorderHelper(
  const vector<int*>& preorder, int* idx_pointer) {

  int* subtree_key = preorder[*idx_pointer];
  ++*idx_pointer;

  if (subtree_key == nullptr) {
    return nullptr;
  }

  auto left_subtree = ReconstructPreorderHelper(preorder, idx_pointer);
  auto right_subtree = ReconstructPreorderHelper(preorder, idx_pointer);

  return make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{*subtree_key, move(left_subtree), move(right_subtree)});
  
}

template <typename T>
void GenPreorderWithNull(const unique_ptr<BinaryTreeNode<T>>& n,
                         vector<T*>* p) {
  if (!n) {
    p->emplace_back(nullptr);
    return;
  }

  p->emplace_back(&(n->data));
  GenPreorderWithNull(n->left, p);
  GenPreorderWithNull(n->right, p);
}

static void SimpleTest() {
  int A[] = {1, 2, 3};
  vector<int*> preorder{A, nullptr, nullptr};
  auto result = ReconstructPreorder(preorder);
  assert(result->data == 1);
  assert(result->left == nullptr);
  assert(result->right == nullptr);

  preorder = {A, nullptr, A + 1, nullptr, nullptr};
  result = ReconstructPreorder(preorder);
  assert(result->data == 1);
  assert(result->left == nullptr);
  assert(result->right->data == 2);

  preorder = {A, nullptr, A + 1, A + 2, nullptr, nullptr, nullptr};
  result = ReconstructPreorder(preorder);
  assert(result->data == 1);
  assert(result->left == nullptr);
  assert(result->right->data == 2);
  assert(result->right->left->data == 3);
  assert(result->right->right == nullptr);
}

int main() {
  SimpleTest();
 
  return 0;
}