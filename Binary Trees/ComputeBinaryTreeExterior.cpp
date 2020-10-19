/*
* ComputeBinaryTreeExterior.cpp
* -----------------
*
* Chapter 10 Question 13
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

bool isLeaf(unique_ptr<BinaryTreeNode<int> >& node) {
  return !node->left && !node->right;
}

// void ExteriorHelper(unique_ptr<BinaryTreeNode<int> >& tree,
//   list<const unique_ptr<BinaryTreeNode<int> >*>& exterior, int depth, int distFromRoot) {
//   if (tree == nullptr) { return; }

//   //if leaf
//   if (isLeaf(tree)) {
//     exterior.push_back(&tree); 
//     return;
//   }
  
//   //if left side of exterior
//   if (depth == abs(distFromRoot) && distFromRoot <= 0) {
//     exterior.push_back(&tree);
//   }
  
//   ExteriorHelper(tree->left, exterior, depth + 1, distFromRoot - 1);
//   ExteriorHelper(tree->right, exterior, depth + 1, distFromRoot + 1);

//   //if right side of exterior
//   if (depth == abs(distFromRoot) && distFromRoot > 0) {
//     exterior.push_back(&tree);
//   }
// }

void getRightBoundaryAndLeaves(unique_ptr<BinaryTreeNode<int> >& subtree, bool isBoundary, 
  list<const unique_ptr<BinaryTreeNode<int> >*>& exterior ) {

  if (subtree != nullptr) {
    
    getRightBoundaryAndLeaves(subtree->left, isBoundary && (subtree->right == nullptr), exterior);
    getRightBoundaryAndLeaves(subtree->right, isBoundary, exterior);

    if (isBoundary || isLeaf(subtree)) {
      exterior.push_back(&subtree);
    }
  }
}

void getLeftBoundaryAndLeaves(unique_ptr<BinaryTreeNode<int> >& subtree, bool isBoundary,
    list<const unique_ptr<BinaryTreeNode<int> >*>& exterior) {
  
  if (subtree != nullptr) {
    if (isBoundary || isLeaf(subtree)) {
      exterior.push_back(&subtree);
    }

    getLeftBoundaryAndLeaves(subtree->left, isBoundary, exterior);
    getLeftBoundaryAndLeaves(subtree->right, isBoundary && (subtree->left == nullptr), exterior);
  }
}

list<const unique_ptr<BinaryTreeNode<int> >*> ExteriorBinaryTree(
  unique_ptr<BinaryTreeNode<int> >& tree) {
    list<const unique_ptr<BinaryTreeNode<int> >*> exterior;

    exterior.push_back(&tree);

    getLeftBoundaryAndLeaves(tree->left, true, exterior);
    getRightBoundaryAndLeaves(tree->right, true, exterior);
    
    return exterior;
} 

unique_ptr<BinaryTreeNode<int>> ReconstructPreorderHelper(const vector<int*>&,
                                                          int*);

unique_ptr<BinaryTreeNode<int> > ReconstructPreorder(const vector<int*>& preorder) {
  int idx_pointer = 0; 
  return ReconstructPreorderHelper(preorder, &idx_pointer);
}

unique_ptr<BinaryTreeNode<int> > ReconstructPreorderHelper(
  const vector<int*>& preorder, int* idx_pointer) {

  int* subtree_key = preorder[*idx_pointer];
  ++*idx_pointer;

  if (subtree_key == nullptr) {
    return nullptr;
  }

  auto left_subtree = ReconstructPreorderHelper(preorder, idx_pointer);
  auto right_subtree = ReconstructPreorderHelper(preorder, idx_pointer);

  return make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{*subtree_key, move(left_subtree), move(right_subtree)});  
}

list<int> CreateOutputList(
    const list<const unique_ptr<BinaryTreeNode<int>>*>& L) {
  list<int> output;
  for (const auto* l : L) {
    output.push_back((*l)->data);
  }
  return output;
}

void SimpleTest() {
  // The example in the book.
  vector<int> A = {314, 6, 271, 28,  0,   561, 3,   17, 6,   2, 1,   401, 641, 257, 271, 28};

  unique_ptr<BinaryTreeNode<int>> tree = ReconstructPreorder(
      {&A[0],   &A[1],   &A[2],   &A[3],   nullptr, nullptr, &A[4],
       nullptr, nullptr, &A[5],   nullptr, &A[6],   &A[7],   nullptr,
       nullptr, nullptr, &A[8],   &A[9],   nullptr, &A[10],  &A[11],
       nullptr, &A[12],  nullptr, nullptr, &A[13],  nullptr, nullptr,
       &A[14],  nullptr, &A[15],  nullptr, nullptr});

  list<int> res = CreateOutputList(ExteriorBinaryTree(tree));
  list<int> golden = {314, 6, 271, 28, 0, 17, 641, 257, 28, 271, 6};

  // for (int x : res) {
  //   cout << x << endl;
  // }
  assert(equal(begin(res), end(res), begin(golden), end(golden)));

  tree->left->left = nullptr;
  res = CreateOutputList(ExteriorBinaryTree(tree));

  golden = {314, 6, 561, 3, 17, 641, 257, 28, 271, 6};
  assert(equal(begin(res), end(res), begin(golden), end(golden)));

  tree->right->right = nullptr;
  res = CreateOutputList(ExteriorBinaryTree(tree));
  golden = {314, 6, 561, 3, 17, 641, 257, 1, 2, 6};
  assert(equal(begin(res), end(res), begin(golden), end(golden)));

  tree->right = nullptr;
  res = CreateOutputList(ExteriorBinaryTree(tree));
  golden = {314, 6, 561, 3, 17};
  assert(equal(begin(res), end(res), begin(golden), end(golden)));
}

int main() {
  SimpleTest(); 
  //        3
  //    2      5
  //  1  0    4 6
  //   -1 -2
  
  unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{3, nullptr, nullptr});
  auto L = ExteriorBinaryTree(tree);
  list<int> result = CreateOutputList(L);
  list<int> golden_result = {3};
  assert(equal(result.begin(), result.end(), golden_result.begin(),
               golden_result.end()));

  tree->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{2, nullptr, nullptr});
  L = ExteriorBinaryTree(tree);
  result = CreateOutputList(L);
  golden_result = {3, 2};
  assert(equal(result.begin(), result.end(), golden_result.begin(),
               golden_result.end()));

  tree->left->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{0, nullptr, nullptr});
  tree->left->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{-1, nullptr, nullptr});
  tree->left->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{-2, nullptr, nullptr});
  tree->left->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  tree->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{5, nullptr, nullptr});
  tree->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{4, nullptr, nullptr});
  tree->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{6, nullptr, nullptr});
  L = ExteriorBinaryTree(tree);
  result = CreateOutputList(L);
  golden_result = {3, 2, 1, -1, -2, 4, 6, 5};
  assert(equal(result.begin(), result.end(), golden_result.begin(),
               golden_result.end()));


  return 0;
}