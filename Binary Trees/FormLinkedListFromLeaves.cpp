/*
* FormLinkedListFromLeaves.cpp
* -----------------
*
* Chapter 10 Question 12
*/

#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

#include "./BinaryTreeNode.h"


list<const unique_ptr<BinaryTreeNode<int>>*> CreateListOfLeaves(unique_ptr<BinaryTreeNode<int>>& tree) {
  list<const unique_ptr<BinaryTreeNode<int>>*> leaves;

  if (tree != nullptr) {
     if (tree->left == nullptr && tree->right == nullptr) {
       cout << "ADD TO LIST: " << tree->data << endl;
      leaves.push_back(&tree);
    } else {
      //traverse left subtree
      auto left_subtree_list = CreateListOfLeaves(tree->left);
      for (auto x : left_subtree_list) { leaves.push_back(x); }

      //traverse right subtree
      auto right_subtree_list = CreateListOfLeaves(tree->right);
      for (auto x : right_subtree_list) { leaves.push_back(x); }
    }
  }
  cout << "SIZE: " << leaves.size() << " DATA: " << (tree != nullptr ? tree->data : 4) << endl;
  return leaves;
}

int main() {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{3, nullptr, nullptr});
  tree->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{2, nullptr, nullptr});
  auto L = CreateListOfLeaves(tree);

  cout << "HERE: " << L.size() << endl;
  //cout << (*L.front())->data << endl;

  assert(L.size() == 1 && (*L.front())->data == 2);

  tree->left->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  tree->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{5, nullptr, nullptr});
  tree->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{4, nullptr, nullptr});
  tree->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{6, nullptr, nullptr});
  L = CreateListOfLeaves(tree);
  list<int> output;
  // should output 1, 4, 6
  for (const auto* l : L) {
    output.push_back((*l)->data);
    cout << (*l)->data << endl;
  }
  list<int> golden_res = {1, 4, 6};
  assert(equal(output.begin(), output.end(), golden_res.begin(),
               golden_res.end()));

  return 0;
}