/*
* SearchMinBST.cpp
* -----------------
*
* Chapter 22 Question 31
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::equal;
using std::make_unique;
using std::map;
using std::unique_ptr;
using std::vector;
using std::unordered_set;

struct Node {
  int data;
  Node *left, *right;
};

bool SearchMinBST(Node *node, int k) {
  if (!node || k < node->data) {
    return false;
  }

  if (node->data == k) return true;

  if (node->right && k >= node->right->data) {
    return SearchMinBST(node->right, k);  
  }   
  return SearchMinBST(node->left, k);
}

int main(int argc, char** argv) {   
  Node root = Node({2});

  Node node1 = Node({3});
  Node node2 = Node({5});
  Node node3 = Node({7});
  Node node4 = Node({11});

  Node node5 = Node({13});
  Node node6 = Node({17});
  Node node7 = Node({19});
  Node node8 = Node({23});

  root.left = &node1;
  root.right = &node5;

  node1.right = &node2;

  node2.left = &node3;
  node2.right = &node4;

  node5.left = &node6;
  node5.right = &node7;

  node7.left = &node8;


  cout << boolalpha << SearchMinBST(&root, 23) << endl;

  return 0;
}


