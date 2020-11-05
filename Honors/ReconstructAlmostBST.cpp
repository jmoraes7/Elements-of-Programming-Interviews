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

struct Node {
  int data;
  Node *left, *right;
};

void ReconstructBSTHelper(Node *root, Node **first, Node **last, Node **prev) {
  if (root) {
    ReconstructBSTHelper(root->left, first, last, prev);

    if (*prev && (*prev)->data > root->data) {
      if (!*first) {
        *first = *prev;
      }
      *last = root;
    }

    *prev = root;

    ReconstructBSTHelper(root->right, first, last, prev);
  }
}

void ReconstructBST(Node *node) {
  Node *first = nullptr, *last = nullptr, *prev = nullptr;

  ReconstructBSTHelper(node, &first, &last, &prev);

  swap(first->data, last->data);
}

void InorderTraversal(Node *node) {
  if (node) {
    InorderTraversal(node->left);
    cout << node->data << " ";
    InorderTraversal(node->right);
  }
}

int main(int argc, char** argv) {   
  Node root = Node({17});
  Node node1 = Node({41});
  Node node2 = Node({8});
  Node node3 = Node({6});
  Node node4 = Node({23});
  Node node5 = Node({21});
  Node node6 = Node({5});
  Node node7 = Node({30});

  root.left = &node1;
  root.right = &node4;

  node1.right = &node2;
  node2.left = &node3;

  node4.left = &node5;
  node4.right = &node6;
  
  node6.left = &node7;

  InorderTraversal(&root);
  cout << endl << "--------" << endl;
  ReconstructBST(&root);

  InorderTraversal(&root);

  return 0;
}


