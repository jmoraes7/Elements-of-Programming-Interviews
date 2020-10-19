/*
* BinaryTreeLock.cpp
* -----------------
*
* Chapter 10 Question 15
*/

#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

#include "./BinaryTreeWithLock.h"

int main() {
  auto root = make_shared<BinaryTreeNode>(BinaryTreeNode());
  root->left() = make_shared<BinaryTreeNode>(BinaryTreeNode());
  root->left()->parent() = root;
  root->right() = make_shared<BinaryTreeNode>(BinaryTreeNode());
  root->right()->parent() = root;
  root->left()->left() = make_shared<BinaryTreeNode>(BinaryTreeNode());
  root->left()->left()->parent() = root->left();
  root->left()->right() = make_shared<BinaryTreeNode>(BinaryTreeNode());
  root->left()->right()->parent() = root->left();

  assert(!root->IsLocked());
  cout << boolalpha << root->IsLocked() << endl;

  assert(root->Lock());
  assert(root->IsLocked());
  cout << boolalpha << root->IsLocked() << endl;
  assert(!root->left()->Lock());
  assert(!root->left()->IsLocked());
  assert(!root->right()->Lock());
  assert(!root->right()->IsLocked());
  assert(!root->left()->left()->Lock());
  assert(!root->left()->left()->IsLocked());
  assert(!root->left()->right()->Lock());
  assert(!root->left()->right()->IsLocked());

  root->Unlock();
  assert(root->left()->Lock());
  assert(!root->Lock());
  assert(!root->left()->left()->Lock());
  assert(!root->IsLocked());

  cout << boolalpha << root->IsLocked() << endl;
  assert(root->right()->Lock());
  assert(root->right()->IsLocked());
  cout << boolalpha << root->right()->IsLocked() << endl;
                 
  return 0;
}