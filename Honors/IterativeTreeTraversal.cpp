/*
* IterativeTreeTraversal.cpp
* -----------------
*
* Chapter 22 Question 15
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

// #include "../Binary Trees/BinaryTreeNode.h"

using std::cout;
using std::endl;
using std::equal;
using std::make_unique;
using std::stack;
using std::unique_ptr;
using std::vector;

template <typename T>
struct BinaryTreeNode {
  T data;
  unique_ptr<BinaryTreeNode<T> > left, right;
  int size;
  bool is_sentinel;
};

vector<int> InorderTraversal(unique_ptr<BinaryTreeNode<int> >& node) {
  //1 2 3 4 5 6
  vector<int> result;
  stack<BinaryTreeNode<int>*> nodes_to_process;
  nodes_to_process.push(node.get());

  while (!nodes_to_process.empty()) {
    auto curr = nodes_to_process.top();
    nodes_to_process.pop();
    if (curr) {      
      nodes_to_process.push(curr->right.get());
      nodes_to_process.push(curr->left.get());
    }
  }

  return result;
}

vector<int> PreorderTraversal(unique_ptr<BinaryTreeNode<int> >& node) {
  //3 2 1 5 4 6
  vector<int> result;
  stack<BinaryTreeNode<int>*> nodes_to_process;
  nodes_to_process.push(node.get());

  while (!nodes_to_process.empty()) {
    auto curr = nodes_to_process.top();
    nodes_to_process.pop();
    if (curr) {
      result.push_back(curr->data);
      
      nodes_to_process.push(curr->right.get());
      nodes_to_process.push(curr->left.get());
    }
  }

  return result;
}

vector<int> PostorderTraversal(unique_ptr<BinaryTreeNode<int> >& node) {
  //1 2 4 6 5 3
  vector<int> result;
  
  stack<BinaryTreeNode<int>*> nodes_to_process;
  nodes_to_process.push(node.get());
  int count = 0;
  while (!nodes_to_process.empty()) {
    auto curr = nodes_to_process.top();
    nodes_to_process.pop();
    if (count == 50) break;
    if (curr) {
      if (curr->is_sentinel) {
        auto processed_node = nodes_to_process.top();
        nodes_to_process.pop();

        result.emplace_back(processed_node->data);
      } else {
        BinaryTreeNode<int>* sentinel = new BinaryTreeNode<int>();
        sentinel->is_sentinel = true;
        
        nodes_to_process.push(curr);
        nodes_to_process.push(sentinel);
        nodes_to_process.push(curr->right.get());
        nodes_to_process.push(curr->left.get());
      }
    }
    count++;
  }

  return result;
}

vector<int> PostorderTraversalAlternate(unique_ptr<BinaryTreeNode<int> >& node) {
  if (node == nullptr) {
    return {};
  }
  
  stack<BinaryTreeNode<int>*> path_stack;
  BinaryTreeNode<int>* prev = nullptr;
  path_stack.push(node.get());
  vector<int> postorder_seq;
  while (!path_stack.empty()) {
    auto curr = path_stack.top();
    if (prev == nullptr || prev->left.get() == curr || prev->right.get() == curr) {
      //We came down to curr from prev
      if (curr->left != nullptr) {
        path_stack.push(curr->left.get());
      } else if (curr->right != nullptr) {
        path_stack.push(curr->right.get());
      } else {
        postorder_seq.push_back(curr->data);
        path_stack.pop();
      }
    } else if (curr->left.get() == prev) {
      //Done with left, so now traverse right
      if (curr->right != nullptr) {
        path_stack.push(curr->right.get());
      } else {
        postorder_seq.push_back(curr->data);
        path_stack.pop();
      }
    } else {
      //Done with right
      postorder_seq.push_back(curr->data);
      path_stack.pop();
    }
    prev = curr;
  }

  return postorder_seq;
}

void PreorderTraversalRecursive(unique_ptr<BinaryTreeNode<int> >& node, vector<int>* A) {
  if (node) {
    A->emplace_back(node->data);
    PreorderTraversalRecursive(node->left, A);
    PreorderTraversalRecursive(node->right, A);
  }
}

void PostorderTraversalRecursive(unique_ptr<BinaryTreeNode<int> >& node, vector<int>* A) {
  if (node) {
    PostorderTraversalRecursive(node->left, A);
    PostorderTraversalRecursive(node->right, A);
    A->emplace_back(node->data);
  }
}

int main(int argc, char** argv) {   
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int> > tree = make_unique<BinaryTreeNode<int>>(
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
  
  auto preorder = PreorderTraversal(tree);

  cout << "PREORDER:" << endl;
  for (int x : preorder) {
    cout << x << " ";
  }
  cout << endl << endl;

  cout << "POSTORDER:" << endl;
  auto postorder = PostorderTraversal(tree);
  for (int x : postorder) {
    cout << x << " ";
  }
  cout << endl << endl;  
  
  return 0;
}


