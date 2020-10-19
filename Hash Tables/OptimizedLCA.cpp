/*
* OptimizedLCA.cpp
* -----------------
*
* Chapter 13 Question 5
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "../Binary Trees/BinaryTreeNodeWithParent.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node1,
                         const unique_ptr<BinaryTreeNode<int>>& node2) {

  auto *iter1 = node1.get(), *iter2 = node2.get();
  unordered_set<const BinaryTreeNode<int>* > visited_nodes;

  while (iter1 || iter2) {
    if (iter1) {
      if (visited_nodes.insert(iter1).second == false) {
        return iter1;
      }

      iter1 = iter1->parent;
    }

    if (iter2) {
      if (visited_nodes.insert(iter2).second == false) {
        return iter2;
      }

      iter2 = iter2->parent;
    }
  }
  
  throw invalid_argument("node1 and node2 are not in the same tree");
}

int main(int argc, char** argv) {  

  unique_ptr<BinaryTreeNode<int>> root = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{3, nullptr, nullptr});
  root->parent = nullptr;
  root->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{2, nullptr, nullptr});
  root->left->parent = root.get();
  root->left->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  root->left->left->parent = root->left.get();
  root->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{5, nullptr, nullptr});
  root->right->parent = root.get();
  root->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{4, nullptr, nullptr});
  root->right->left->parent = root->right.get();
  root->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{6, nullptr, nullptr});
  root->right->right->parent = root->right.get();

  // should output 3
  assert(LCA(root->left, root->right)->data == 3);
  cout << (LCA(root->left, root->right))->data << endl;
  // should output 5
  assert(LCA(root->right->left, root->right->right)->data == 5);
  cout << (LCA(root->right->left, root->right->right)->data) << endl;

  return 0;
}
