/*
* ComputeKthNodeInorderTraversal.cpp
* -----------------
*
* Chapter 10 Question 7
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

#include "./BinaryTreeNode.h"

BinaryTreeNode<int>* getKthNode(const unique_ptr<BinaryTreeNode<int> >& tree, int k) {
  auto *iter = tree.get();


  while (iter != nullptr) {
    int left_size = (iter->left != nullptr) ? iter->left->size : 0;
    cout << left_size << " - " << k << endl; 

    if (k == left_size + 1) { return iter; }

    if (k <= left_size) { iter = iter->left.get(); }
    
    else {
      iter = iter->right.get();
      k -= (left_size + 1);
    }
  }
  
  return nullptr;
}

int main(int argc, char* argv[]) {
   //  size field
  //      6
  //    2   3
  //  1    1 1
  //
  //  data field
  //      3
  //    2   5
  //  1    4 6
  auto root = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
  root->size = 6;
  root->data = 3;
  root->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
  root->left->size = 2;
  root->left->data = 2;
  root->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
  root->left->left->size = 1;
  root->left->left->data = 1;
  root->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
  root->right->size = 3;
  root->right->data = 5;
  root->right->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
  root->right->left->size = 1;
  root->right->left->data = 4;
  root->right->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
  root->right->right->size = 1;
  root->right->right->data = 6;
  
  // 0th node does not exist - leftmost node is node 1
  assert(nullptr == getKthNode(root, 0));
  // should output 1
  // assert(getKthNode(root, 1)->data == 1);
  // cout << (getKthNode(root, 1))->data << endl;
  // // should output 2
  // assert(getKthNode(root, 2)->data == 2);
  // cout << (getKthNode(root, 2))->data << endl;
  // // should output 3
  // assert(getKthNode(root, 3)->data == 3);
  // cout << (getKthNode(root, 3))->data << endl;
  // // should output 4
  // assert(getKthNode(root, 4)->data == 4);
  // cout << (getKthNode(root, 4))->data << endl;
  // // should output 5
  // assert(getKthNode(root, 5)->data == 5);
  // cout << (getKthNode(root, 5))->data << endl;
  // // should output 6
  // assert(getKthNode(root, 6)->data == 6);
  // cout << (getKthNode(root, 6))->data << endl;
  // assert(nullptr == getKthNode(root, 7));
  
  return 0;
}