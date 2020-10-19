/*
* FindFirstGreaterThanK.cpp
* -----------------
*
* Chapter 15 Question 3
*/
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::unique_ptr;

BinaryTreeNode<int>* FindFirstGreaterThanK(const unique_ptr<BinaryTreeNode<int> >& tree, int k) {
  BinaryTreeNode<int>* first_greater_so_far = nullptr, *curr = tree.get();

  while (curr) {
    if (curr->data <= k) {
      curr = curr->right.get();
    } else {
      first_greater_so_far = curr;
      curr = curr->left.get();
    }
  }

  return first_greater_so_far;
}

int main(int argc, char** argv) {    
   //      3
  //    2   5
  //  1    4 6
  auto tree = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{3});
  tree->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{2});
  tree->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{1});
  tree->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{5});
  tree->right->left =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{4});
  tree->right->right =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{6});
  // should output true.
  
  auto node = FindFirstGreaterThanK(tree, 3);

  cout << node->data << endl;

  return 0;
}
