/*
* LowestCommonAncestorWithParent.cpp
* -----------------
*
* Chapter 10 Question 4
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./BinaryTreeNodeWithParent.h"

using namespace std;

int getDepth(const BinaryTreeNode<int>* node) {
  int depth = 0; 

  while (node->parent) {
    depth++;
    node = node->parent;
  } 

  return depth;
}
BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int> >& node1,
                          const unique_ptr<BinaryTreeNode<int> >& node2) {
  auto *iter1 = node1.get(), *iter2 = node2.get();
  int depth1 = getDepth(node1.get());
  int depth2 = getDepth(node2.get());

  if (depth2 > depth1) {
    swap(iter1, iter2);
  }

  int depth_diff = abs(depth1 - depth2);
  while (depth_diff--) {
    iter1 = iter1->parent;
  }

  while (iter1 != iter2) {
    iter1 = iter1->parent;
    iter2 = iter2->parent;
  }

  return iter1;
}

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6

  unique_ptr<BinaryTreeNode<int> > root = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{3, nullptr, nullptr});
  root->parent = nullptr;
  root->left = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{2, nullptr, nullptr});
  root->left->parent = root.get();
  
  root->left->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  root->left->left->parent = root->left.get();
  root->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{5, nullptr, nullptr});
  root->right->parent = root.get();
  root->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{4, nullptr, nullptr});
  root->right->left->parent = root->right.get();
  root->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{6, nullptr, nullptr});
  root->right->right->parent = root->right.get();

  // should output 3
  assert(LCA(root->left, root->right)->data == 3);
  cout << (LCA(root->left, root->right))->data << endl;
  // should output 5
  assert(LCA(root->right->left, root->right->right)->data == 5);
  cout << (LCA(root->right->left, root->right->right)->data) << endl;

  return 0;
}