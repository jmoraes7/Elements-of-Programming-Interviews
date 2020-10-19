/*
* ComputeRightSiblingTree.cpp
* -----------------
*
* Chapter 10 Question 14
*/

#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

#include "./BinaryTreeNodeWithNext.h"

void populateChildNextFields(BinaryTreeNode<int>* start_node) {
  auto iter = start_node;
  
  while (iter) {
    iter->left->next = iter->right;

    cout << "LEFT: " << iter->left->data << " RIGHT: " << iter->right->data << endl;

    if (iter->next) {
      iter->right->next = iter->next->left;
    }

    iter = iter->next.get();
  }
}

void computeRightSiblingTree(BinaryTreeNode<int>* tree) {
  auto left_start = tree;
  while (left_start && left_start->left) {
    populateChildNextFields(left_start);
    left_start = left_start->left.get();
  }
}

int main() {
  //        3
  //    2      5
  //  1  0    4 6
  //   -1 -2
  
  shared_ptr<BinaryTreeNode<int>> tree = make_shared<BinaryTreeNode<int>>(BinaryTreeNode<int>{3, nullptr, nullptr});

  tree->left = make_shared<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{2, nullptr, nullptr});
  

  tree->left->right = make_shared<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{0, nullptr, nullptr});
  tree->left->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{-1, nullptr, nullptr});
  tree->left->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{-2, nullptr, nullptr});
  tree->left->left = make_shared<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  tree->right = make_shared<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{5, nullptr, nullptr});
  tree->right->left = make_shared<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{4, nullptr, nullptr});
  tree->right->right = make_shared<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{6, nullptr, nullptr});
  computeRightSiblingTree(tree.get());
  
  assert(tree->left->next->data == 5);

  assert(tree->left->left->next->data == 0); 
  assert(tree->left->left->next->next->data == 4);
  assert(tree->left->left->next->next->next->data == 6);
               
  return 0;
}