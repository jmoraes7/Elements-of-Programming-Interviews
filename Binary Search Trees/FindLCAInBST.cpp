/*
* FindLCAInBST.cpp
* -----------------
*
* Chapter 15 Question 5
*/
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::unique_ptr;

BinaryTreeNode<int>* FindLCA(const unique_ptr<BinaryTreeNode<int> >& tree,
                              const unique_ptr<BinaryTreeNode<int> >& smaller,
                              const unique_ptr<BinaryTreeNode<int> >& bigger) {
  if (!tree) { return nullptr; }

  
  auto* parent = tree.get();

  while (parent->data < smaller->data || parent->data > bigger->data) {
    while (parent->data < smaller->data) {
      parent = parent->right.get();
    }

    while (parent->data > bigger->data) {
      parent = parent->left.get();
    }
  }

  return parent;
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
  
  auto LCA = FindLCA(tree, tree->right->left,  tree->right);

  cout << LCA->data << endl;
  return 0;
}
