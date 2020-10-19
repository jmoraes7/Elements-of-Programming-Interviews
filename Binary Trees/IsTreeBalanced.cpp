/*
* IsTreeBalanced.cpp
* -----------------
*
* Chapter 10 Question 1
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

#include "./BinaryTreeNode.h"

using namespace std;

struct Result {
  bool isBalanced;
  int height;
};

Result isBalancedHelper(unique_ptr<BinaryTreeNode<int> >& tree) {
  if (tree == nullptr) { return {true, -1}; }

  auto left = isBalancedHelper(tree->left);
  auto right = isBalancedHelper(tree->right);

  if (left.isBalanced == false || 
    right.isBalanced == false ||
    abs(left.height - right.height) > 1) {
    return { false, -1 }; 
  }

  return Result{true, max(left.height, right.height) + 1 };
}

Result isBalancedHelperClean(unique_ptr<BinaryTreeNode<int> >& tree) {
  if (tree == nullptr) {
    return Result{true, -1};
  }

  auto left = isBalancedHelperClean(tree->left);
  if (!left.isBalanced) {
    return Result{ false, 0 };
  }

  auto right = isBalancedHelperClean(tree->right);
  if (!right.isBalanced) {
    return Result{ false, 0 }; 
  }

  bool isBalanced = abs(left.height - right.height) <= 1;
  int height = max(left.height, right.height) + 1;

  return Result{ isBalanced, height }; 

}

bool isBalanced(unique_ptr<BinaryTreeNode<int> >& tree) {
  
  return isBalancedHelper(tree).isBalanced;
}

int main(int argc, char* argv[]) {
   //  balanced binary tree test
  //      3
  //    2   5
  //  1    4 6

  unique_ptr<BinaryTreeNode<int> > tree =
      make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  tree->left = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  tree->left->left = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  tree->right = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  tree->right->left = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  tree->right->right =
      make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  
  assert(isBalanced(tree) == true);
  cout << boolalpha << isBalanced(tree) << endl;
  
  // Non-balanced binary tree test.
  tree = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  tree->left = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  tree->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
  
  assert(isBalanced(tree) == false);
  cout << boolalpha << isBalanced(tree) << endl;
  
  return 0;
}