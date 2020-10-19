/*
* ConstructTreeFromTraversalData.cpp
* -----------------
*
* Chapter 10 Question 10
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

#include "./BinaryTreeNodeWithParent.h"


unique_ptr<BinaryTreeNode<int> > BinaryTreeFromPreorderInorderHelper(
  const vector<int>& preorder, size_t preorder_start, size_t preorder_end,
  size_t inorder_start, size_t inorder_end,
  unordered_map<int, size_t> node_to_inorder_idx) {
  
  if (preorder_end <= preorder_start || inorder_end <= inorder_start) {
    return nullptr;
  }

  int root_val = preorder[preorder_start];
  size_t root_idx = node_to_inorder_idx.at(root_val);

  size_t left_subtree_size = root_idx - inorder_start;

  //unique_ptr<BinaryTreeNode<int> > left_subtree = BinaryTreeFromPreorderInorderHelper(preorder, preorder_start + 1, preorder_start + 1 + left_subtree_size,
  //  inorder_start, root_idx, node_to_inorder_idx);

  // auto right_subtree = BinaryTreeFromPreorderInorderHelper(preorder, preorder_start + 1 + left_subtree_size, preorder_end,
  //   root_idx + 1, inorder_end, node_to_inorder_idx);
  
  return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
    root_val,
    BinaryTreeFromPreorderInorderHelper(preorder, preorder_start + 1, preorder_start + 1 + left_subtree_size, 
      inorder_start, root_idx, node_to_inorder_idx),
    BinaryTreeFromPreorderInorderHelper(preorder, preorder_start + 1 + left_subtree_size, preorder_end,
     root_idx + 1, inorder_end, node_to_inorder_idx)}
  );  
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  
  unordered_map<int, size_t> node_to_inorder_idx;
  for (size_t i = 0; i < inorder.size(); ++i) {
    node_to_inorder_idx.insert({inorder[i], i}); 
  }
  
  cout << node_to_inorder_idx.at(1) << endl;

  return BinaryTreeFromPreorderInorderHelper(
    preorder, 0, preorder.size(), 0, inorder.size(), node_to_inorder_idx);
}

void SimpleTest() {
  cout << "TEST";

  auto res = BinaryTreeFromPreorderInorder({1}, {1});

  assert(res->data == 1);

  res = BinaryTreeFromPreorderInorder({2, 1}, {1, 2});
  assert(res->data == 2 && res->left->data == 1 && res->right == nullptr);

  int N = 100;
  vector<int> inorder, preorder;
  for (int i = 0; i < N; ++i) {
    inorder.push_back(i);
    preorder.push_back((N - 1) - i);
  }

  res = BinaryTreeFromPreorderInorder(preorder, inorder);
  assert(res->data == N - 1 && res->left->data == N - 2 &&
         res->right == nullptr);
}

int main() {
  SimpleTest();
  // default_random_engine gen((random_device())());
  // for (int times = 0; times < 1000; ++times) {
  //   cout << times << endl;
  //   int n;
  //   if (argc == 2) {
  //     n = atoi(argv[1]);
  //   } else {
  //     uniform_int_distribution<int> dis(1, 10000);
  //     n = dis(gen);
  //   }
  //   unique_ptr<BinaryTreeNode<int>> root =
  //       generate_rand_binary_tree<int>(n, true);
  //   vector<int> pre = generate_preorder(root);
  //   vector<int> in = generate_inorder(root);
  //   auto res = BinaryTreeFromPreorderInorder(pre, in);
  //   assert(is_two_binary_trees_equal<int>(root, res));
  //   delete_binary_tree(&root);
  //   delete_binary_tree(&res);
  // }
  return 0;
}