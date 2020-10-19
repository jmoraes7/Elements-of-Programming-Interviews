/*
* LowestCommonAncestorNoParent.cpp
* -----------------
*
* Chapter 10 Question 3
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
  int num_target_nodes;
  BinaryTreeNode<int>* ancestor;
};

/*
* Runtime is O(n)
*/
Result LCAFastHelper(const unique_ptr<BinaryTreeNode<int> >& tree,
                                    const unique_ptr<BinaryTreeNode<int> >& node1,
                                    const unique_ptr<BinaryTreeNode<int> >& node2) {
  
  if (tree == nullptr) { return Result{ 0, nullptr }; }
  
  

  auto left_result = LCAFastHelper(tree->left, node1, node2);
  if (left_result.num_target_nodes == 2) {
    return left_result;
  }

  auto right_result = LCAFastHelper(tree->right, node1, node2);
  if (right_result.num_target_nodes == 2) {
    return right_result;
  }

  int num_target_nodes = left_result.num_target_nodes + 
                          right_result.num_target_nodes + 
                          (tree == node1 || tree == node2);

  return Result{ num_target_nodes, (num_target_nodes == 2 ? tree.get() : nullptr) };


}
BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int> >& tree,
                                    const unique_ptr<BinaryTreeNode<int> >& node1,
                                    const unique_ptr<BinaryTreeNode<int> >& node2) {
  
  if (node1 == node2) { return node1.get(); }
   
  return LCAFastHelper(tree, node1, node2).ancestor;
}

int getNumTargetNodesInTree(unique_ptr<BinaryTreeNode<int> >& tree, 
                        const unique_ptr<BinaryTreeNode<int> >& node1,
                        const unique_ptr<BinaryTreeNode<int> >& node2) {
  
  if (tree == nullptr) { return 0; }

  int count = 0;

  if (tree->data == node1->data) { count++; }

  if (tree->data == node2->data) { count++; }

  count += getNumTargetNodesInTree(tree->left, node1, node2);

  //if both nodes haven't been located yet
  if (count != 2) { 
    count += getNumTargetNodesInTree(tree->right, node1, node2 );
  }

  return count;
}

/*
* Worst case runtime is O(n^2)
*/
BinaryTreeNode<int>* LCASlower(const unique_ptr<BinaryTreeNode<int> >& tree,
                                    const unique_ptr<BinaryTreeNode<int> >& node1,
                                    const unique_ptr<BinaryTreeNode<int> >& node2) {
  
  if (tree == node1 || tree == node2) { return tree.get(); }
  
  int num_nodes_in_left_subtree = getNumTargetNodesInTree(tree->left, node1, node2);

  if (num_nodes_in_left_subtree == 2) {
    return LCA(tree->left, node1, node2);
  }

  if (num_nodes_in_left_subtree == 1) {
    return tree.get();
  }

  return LCA(tree->right, node1, node2);
}

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{3, nullptr, nullptr});
  tree->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{2, nullptr, nullptr});
  tree->left->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  tree->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{5, nullptr, nullptr});
  tree->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{4, nullptr, nullptr});
  tree->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{6, nullptr, nullptr});
  // should output 3
  auto x = LCA(tree, tree->left, tree->right);
  assert(x->data == 3);
  cout << x->data << endl;
  // should output 5
  x = LCA(tree, tree->right->left, tree->right->right);
  assert(x->data == 5);
  cout << x->data << endl;
  // should output 5
  x = LCA(tree, tree->right, tree->right->right);
  assert(x->data == 5);
  cout << x->data << endl;
  // should output 3
  x = LCA(tree, tree->left->left, tree->right->right);
  assert(x->data == 3);
  cout << x->data << endl;
  // should output 3
  x = LCA(tree, tree->left->left, tree);
  assert(x->data == 3);
  cout << x->data << endl;
  // should output 2
  x = LCA(tree, tree->left, tree->left);
  assert(x->data == 2);
  cout << x->data << endl;

  return 0;
}