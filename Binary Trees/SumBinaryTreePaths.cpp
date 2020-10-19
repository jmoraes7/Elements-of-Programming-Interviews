/*
* SumBinaryTreePaths.cpp
* -----------------
*
* Chapter 10 Question 5
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./BinaryTreeNode.h"

using namespace std;

int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int> >& node, int partial_sum) {
  if (node == nullptr) {
    return 0;
  }

  partial_sum = partial_sum * 2 + node->data;

  //if leaf
  if (node->right == nullptr && node->left == nullptr) {
    return partial_sum;
  }

  //if not leaf
  return SumRootToLeafHelper(node->left, partial_sum) +
          SumRootToLeafHelper(node->right, partial_sum);
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int> >& tree) {
  return SumRootToLeafHelper(tree, 0);
}

int main(int argc, char* argv[]) {
   //      1
  //    1   0
  //  0    1 0 ---- 6 + 5 + 4 = 15
  unique_ptr<BinaryTreeNode<int>> root = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  assert(SumRootToLeaf(root) == 1);
  root->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  assert(SumRootToLeaf(root) == 3);
  root->left->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{0, nullptr, nullptr});
  assert(SumRootToLeaf(root) == 6);
  root->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{0, nullptr, nullptr});
  assert(SumRootToLeaf(root) == 8);
  root->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  assert(SumRootToLeaf(root) == 11);
  root->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{0, nullptr, nullptr});
  assert(SumRootToLeaf(root) == 15);
  
  return 0;
}