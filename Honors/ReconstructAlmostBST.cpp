/*
* ReconstructAlmostBST.cpp
* -----------------
*
* Chapter 22 Question 29
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::make_unique;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::unique_ptr;
using std::stoi;
using std::vector;

std::unique_ptr<BinaryTreeNode<int> > ReconstructAlmostBST(std::unique_ptr<BinaryTreeNode<int> tree) {
  
  return nullptr;
}

int main(int argc, char** argv) {   
  auto root = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{17});
  
  auto node1 = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{41});
  auto node2 = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{8});
  auto node3 = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{6});
  
  unique_ptr<BinaryTreeNode<int> > node4 = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{23});
  unique_ptr<BinaryTreeNode<int> > node5 = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{21});
  unique_ptr<BinaryTreeNode<int> > node6 = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{5});
  unique_ptr<BinaryTreeNode<int> > node7 = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{30});

  root.left = node1;
  root->right = node4;

  node1->right = node2;
  node2->left = node3;

  node4->left = node5;
  node4->right = node6;

  node6->left = node7;




  return 0;
}


