/*
* FindKLargestElements.cpp
* -----------------
*
* Chapter 15 Question 4
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

void FindKLargestElementsHelper(const unique_ptr<BinaryTreeNode<int> >& tree, int k, vector<int>& elements) {
  if (tree == nullptr || elements.size() == k) {
    return;
  }

  if (tree && elements.size() < k) {
    FindKLargestElementsHelper(tree->right, k, elements);

    if (elements.size() < k) {
      elements.push_back(tree->data);
      FindKLargestElementsHelper(tree->left, k, elements);
    }
  }
}


vector<int> FindKLargestElements(const unique_ptr<BinaryTreeNode<int> >& tree, int k) {
  vector<int> elements;
  FindKLargestElementsHelper(tree, k, elements);
  
  return elements;
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
  
  auto kLargestElements = FindKLargestElements(tree, 2);

  for (int elem : kLargestElements) {
    cout << elem << endl;
  }

  return 0;
}
