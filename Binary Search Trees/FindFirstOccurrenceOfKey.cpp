/*
* FindFirstOccurrenceOfKey.cpp
* -----------------
*
* Chapter 15 Question 2
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


BinaryTreeNode<int>* FindFirstOccurrenceOfKeyIterative(const unique_ptr<BinaryTreeNode<int> >& tree, int k) {
  BinaryTreeNode<int>* first_so_far, *curr = tree.get();
  while (curr) {
    if (curr->data == k) {
      first_so_far = curr;
      curr = curr->left.get();
    } else if (curr->data < k) {
      curr = curr->right.get();
    } else { //curr->data > k
      curr = curr->left.get();
    }
  }

  return first_so_far;
}

BinaryTreeNode<int>* FindFirstOccurrenceOfKey(const unique_ptr<BinaryTreeNode<int> >& tree, int k) {
  if (tree == nullptr) {
    return nullptr;
  } else if (tree->data == k) {
    auto* node = FindFirstOccurrenceOfKey(tree->left, k);
    return node ? node : tree.get();
  } 

  return FindFirstOccurrenceOfKey(tree->data > k ? tree->left : tree->right, k);
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
  
  auto node = FindFirstOccurrenceOfKeyIterative(tree, 4);

  cout << node->data << endl;

  return 0;
}
