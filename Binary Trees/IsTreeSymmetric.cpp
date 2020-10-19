/*
* IsTreeSymmetric.cpp
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

bool isSymmetricHelper(unique_ptr<BinaryTreeNode<int> >& node1, unique_ptr<BinaryTreeNode<int> >& node2) {
  if (node1 == nullptr && node2 == nullptr) {
    return true;
  }

  if (node1 == nullptr || node2 == nullptr || node1->data != node2->data) {
    return false;
  }

  return isSymmetricHelper(node1->right, node2->left) && isSymmetricHelper(node1->left, node2->right);
}


bool isSymmetricHelperClean(unique_ptr<BinaryTreeNode<int> >& node1, unique_ptr<BinaryTreeNode<int> >& node2) {
  if (node1 == nullptr && node2 == nullptr) {
    return true;
  }

  if (node1 != nullptr && node2 != nullptr) {
    return node1->data == node2->data &&
        isSymmetricHelperClean(node1->right, node2->left) && 
        isSymmetricHelperClean(node1->left, node2->right);
  }

  //one subtree is empty, the other is not
  return true; //isSymmetricHelper(node1->right, node2->left) && isSymmetricHelper(node1->left, node2->right);
}

bool isSymmetric(unique_ptr<BinaryTreeNode<int> >& tree) {
  
  return isSymmetricHelper(tree->right, tree->left);
}

int main(int argc, char* argv[]) {
   //  balanced binary tree test
  //      3
  //    2   5
  //  1    4 6

  unique_ptr<BinaryTreeNode<int> > tree = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{3, nullptr});
  
  tree->left = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{2, nullptr, nullptr});
  tree->left->right = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{4, nullptr, nullptr});
  //tree->left->left = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());

  tree->right = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{2, nullptr, nullptr});
  tree->right->left = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{4, nullptr, nullptr});
  //tree->right->right = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  
  assert(isSymmetric(tree) == true);
  cout << boolalpha << isSymmetric(tree) << endl;
  
  // tree = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  // tree->left = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>());
  tree->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());
  //tree->right->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>());

  
  assert(isSymmetric(tree) == true);
  cout << boolalpha << isSymmetric(tree) << endl;
  
  return 0;
}