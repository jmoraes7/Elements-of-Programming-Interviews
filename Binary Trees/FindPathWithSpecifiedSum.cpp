/*
* FindPathWithSpecifiedSum.cpp
* -----------------
*
* Chapter 10 Question 6
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./BinaryTreeNode.h"

using namespace std;

bool HasPathSumHelper(const unique_ptr<BinaryTreeNode<int> >& tree, int target_sum, int partial_sum) {
  if (tree == nullptr) {
    return false;
  }

  partial_sum += tree->data;

  if (tree->left == nullptr && tree->right == nullptr) {
    return partial_sum == target_sum;
  }

  return HasPathSumHelper(tree->left, target_sum, partial_sum) || 
        HasPathSumHelper(tree->right, target_sum, partial_sum);
}

bool HasPathSum(const unique_ptr<BinaryTreeNode<int> >& tree, int target_sum) {
  
  return HasPathSumHelper(tree, target_sum, 0);
}

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{3, nullptr, nullptr});
  assert(HasPathSum(tree, 3));
  tree->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{2, nullptr, nullptr});
  assert(HasPathSum(tree, 5));
  tree->left->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  assert(HasPathSum(tree, 6));
  tree->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{5, nullptr, nullptr});
  assert(HasPathSum(tree, 8));
  assert(!HasPathSum(tree, 7));
  tree->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{4, nullptr, nullptr});
  assert(HasPathSum(tree, 12));
  assert(!HasPathSum(tree, 1));
  assert(!HasPathSum(tree, 3));
  assert(!HasPathSum(tree, 5));
  tree->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{6, nullptr, nullptr});
  assert(HasPathSum(tree, 6));
  assert(!HasPathSum(tree, 7));
  assert(HasPathSum(tree, 14));
  assert(!HasPathSum(tree, -1));
  assert(!HasPathSum(tree, numeric_limits<int>::max()));
  assert(!HasPathSum(tree, numeric_limits<int>::min()));
  
  return 0;
}