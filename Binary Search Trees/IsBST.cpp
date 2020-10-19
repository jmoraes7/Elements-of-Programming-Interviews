/*
* IsBST.cpp
* -----------------
*
* Chapter 15 Question 1
*/
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::queue;
using std::unique_ptr;

struct QueueEntry {
  const unique_ptr<BinaryTreeNode<int> >& node;
  int low_range, high_range;
};

bool IsBinaryTreeBSTWithQueue(const unique_ptr<BinaryTreeNode<int> >& tree) {
  if (tree == nullptr) { return true; }

  queue<QueueEntry> queue;
  queue.push({tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()});

  while (!queue.empty()) { 
    QueueEntry entry = queue.front();
    queue.pop();

    auto& node = entry.node;

    if (node->data < entry.low_range || node->data > entry.high_range) {
      return false;
    }

    //push left child
    if (node->left) {
      queue.push({node->left, entry.low_range, node->data});
    }
    
    //push right child
    if (node->right) {
      queue.push({node->right, node->data, entry.high_range});
    }
  }

  return true;
}

bool IsBinaryTreeBSTConstantSpace(const unique_ptr<BinaryTreeNode<int> >& node) {
  if (node == nullptr) { return true; }


  
  return false;
}


bool AreKeysInRange(const unique_ptr<BinaryTreeNode<int> >& node, int low_range, int high_range) {
  if (node == nullptr) {
    return true;
  }

  if (node->data < low_range || node->data > high_range) {
    return false;
  }

  return AreKeysInRange(node->left, low_range, node->data) &&
          AreKeysInRange(node->right, node->data, high_range);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int> >& node) {

  return AreKeysInRange(node, std::numeric_limits<int>::min(),
                          std::numeric_limits<int>::max());
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
  assert(IsBinaryTreeBST(tree) == true);
  cout << boolalpha << IsBinaryTreeBST(tree) << endl;
  //      10
  //    2   5
  //  1    4 6
  tree->data = 10;
  // should output false.
  assert(!IsBinaryTreeBST(tree));
  cout << boolalpha << IsBinaryTreeBST(tree) << endl;
  // should output true.
  assert(IsBinaryTreeBST(nullptr) == true);
  cout << boolalpha << IsBinaryTreeBST(nullptr) << endl;

  return 0;
}
