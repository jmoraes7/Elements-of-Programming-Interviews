/*
* InOrderTraversalConstantSpace.cpp
* -----------------
*
* Chapter 10 Question 8
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

#include "./BinaryTreeNodeWithParent.h"

// vector<int> traverseInOrder(const unique_ptr<BinaryTreeNode<int> >& tree) {
//   vector<int> elements;

//   auto *iter = tree.get();
//   bool node_already_traversed = false;

//   while (iter != nullptr) {
//     //find leftmost node
//     while (iter->left) { iter = iter->left.get(); }

//     //traverse up until you find an unvisited right subtree
//     do {      
//       if (!node_already_traversed) { elements.push_back(iter->data); }

//       if (iter->parent) {
//         node_already_traversed = iter == iter->parent->right.get();
//       }

//       iter = iter->parent;
//     } while (iter && (node_already_traversed || iter->right == nullptr));

//     //add element with right subtree and then step into right subtree
//     if (iter) { 
//       elements.push_back(iter->data);
//       iter = iter->right.get(); 
//     }
//   }
  
//   return elements;
// }

vector<int> traverseInOrder(const unique_ptr<BinaryTreeNode<int> >& tree) { 
  BinaryTreeNode<int> *prev = nullptr, *curr = tree.get();
  vector<int> elements;

  while (curr != nullptr) {
    BinaryTreeNode<int> *next; 

    //we came down to curr from prev
    if (curr->parent == prev) {
      
      //done with left traversal, so go right if not empty. Otherwise, go up
      if (curr->left == nullptr) {
        elements.push_back(curr->data);

        next = curr->right ? curr->right.get() : curr->parent;
      } else {
        next = curr->left.get();
      }
    }
  
    //just visited left subtree - we came up to curr from its left subtree
    else if (curr->left.get() == prev) {
      elements.push_back(curr->data);

      next = curr->right ? curr->right.get() : curr->parent;
    }

    //just visited right subtree - done with both children, so go up
    else { 
      next = curr->parent;
    }
    prev = curr;
    curr = next;
  }

  return elements;
}


int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> root = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{3, nullptr, nullptr});
  root->parent = nullptr;
  auto result = traverseInOrder(root);
  vector<int> golden_res = {3};
  assert(equal(golden_res.begin(), golden_res.end(), result.begin(),
               result.end()));

  root->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{2, nullptr, nullptr});
  root->left->parent = root.get();
  root->left->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  root->left->left->parent = root->left.get();
  result = traverseInOrder(root);
  golden_res = {1, 2, 3};
  assert(equal(golden_res.begin(), golden_res.end(), result.begin(),
               result.end()));

  for (int x : result) {
    cout << x << " - ";
  }
  cout << endl;

  auto *iter = root.get();
  iter = iter->left->right.get();
  cout << iter << endl;
  root->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{5, nullptr, nullptr});
  root->right->parent = root.get();
  root->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{4, nullptr, nullptr});
  root->right->left->parent = root->right.get();
  root->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{6, nullptr, nullptr});
  root->right->right->parent = root->right.get();

  result = traverseInOrder(root);
  golden_res = {1, 2, 3, 4, 5, 6};
  assert(equal(golden_res.begin(), golden_res.end(), result.begin(),
               result.end()));
  
  return 0;
}