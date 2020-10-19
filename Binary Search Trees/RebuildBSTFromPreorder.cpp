/*
* RebuildBSTFromPreorder.cpp
* -----------------
*
* Chapter 15 Question 6
*/
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::unique_ptr;


/*
* Postorder function
*/ 
unique_ptr<BinaryTreeNode<int> > RebuildBSTFromPostOrderHelperFast(
    const vector<int>& postorder_sequence, int lower_bound, int upper_bound, int* root_idx) {
  
  if (*root_idx == -1) {
    return nullptr;
  }

  int root = postorder_sequence[*root_idx];
  if (root < lower_bound || root > upper_bound) {
    return nullptr;
  }

  --*root_idx;

  auto right_child = RebuildBSTFromPostOrderHelperFast(postorder_sequence, root, upper_bound, root_idx);
  auto left_child = RebuildBSTFromPostOrderHelperFast(postorder_sequence, lower_bound, root, root_idx);

  return make_unique<BinaryTreeNode<int>>(
          BinaryTreeNode<int>{
            root,
            move(left_child),
            move(right_child),
          });

}

unique_ptr<BinaryTreeNode<int> > RebuildBSTFromPostOrderFast(const vector<int>& postorder_sequence) {
  int root_idx = postorder_sequence.size() - 1;

  return RebuildBSTFromPostOrderHelperFast(
    postorder_sequence, 
    std::numeric_limits<int>::min(), 
    std::numeric_limits<int>::max(),
    &root_idx);
}

unique_ptr<BinaryTreeNode<int> > RebuildBSTFromPostOrderHelper(
    const vector<int>& postorder_sequence, int start, int end) {
  
  if (start < end) {
  
    int transition_point = start;
    while (transition_point < end && 
          postorder_sequence[transition_point] < postorder_sequence[end - 1]) {
      ++transition_point;
    }

    return make_unique<BinaryTreeNode<int>>(
            BinaryTreeNode<int>{
              postorder_sequence[end - 1],
              RebuildBSTFromPostOrderHelper(postorder_sequence, start, transition_point),
              RebuildBSTFromPostOrderHelper(postorder_sequence, transition_point, end - 1)
            });

  }

  return nullptr;
}

unique_ptr<BinaryTreeNode<int> > RebuildBSTFromPostOrder(const vector<int>& postorder_sequence) {
  return RebuildBSTFromPostOrderHelper(postorder_sequence, 0, postorder_sequence.size());
}

/*
* Preorder function
*/ 

unique_ptr<BinaryTreeNode<int> > RebuildBSTFromPreorderHelperFast(
  const vector<int>& preorder_sequence, int lower_bound, int upper_bound, int* root_idx) {
  if (*root_idx == preorder_sequence.size()) {
    return nullptr;
  }

  int root = preorder_sequence[*root_idx];
  if (root < lower_bound || root > upper_bound) {
    return nullptr;
  }

  ++*root_idx;

  return make_unique<BinaryTreeNode<int>>(
          BinaryTreeNode<int>{
            root, 
            RebuildBSTFromPreorderHelperFast(preorder_sequence, lower_bound, root, root_idx),
            RebuildBSTFromPreorderHelperFast(preorder_sequence, root, upper_bound, root_idx)
          });

}

unique_ptr<BinaryTreeNode<int> > RebuildBSTFromPreorderFast(
  const vector<int>& preorder_sequence) {
  int root_idx = 0;

  return RebuildBSTFromPreorderHelperFast(
            preorder_sequence, 
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max(),
            &root_idx);
}

unique_ptr<BinaryTreeNode<int> > RebuildBSTFromPreorderHelper(
  const vector<int>& preorder_sequence, int start, int end) {
  if (start >= end) { 
    return nullptr;
  }
  
  int root_val = preorder_sequence[start];

  int transition_point = start + 1;
  while (transition_point < end && preorder_sequence[transition_point] < root_val) {
    ++transition_point;
  }

  return make_unique<BinaryTreeNode<int>>(
          BinaryTreeNode<int>{
            root_val, 
            RebuildBSTFromPreorderHelper(preorder_sequence, start + 1, transition_point),
            RebuildBSTFromPreorderHelper(preorder_sequence, transition_point, end)
          });
}

unique_ptr<BinaryTreeNode<int> > RebuildBSTFromPreorder(
  const vector<int>& preorder_sequence) {

  return RebuildBSTFromPreorderHelper(preorder_sequence, 0, preorder_sequence.size());
}

int main(int argc, char** argv) {    
  //      3
  //    2   5
  //  1    4  6
  // should output 1, 2, 3, 4, 5, 6
  // preorder [3, 2, 1, 5, 4, 6]
  vector<int> preorder{3, 2, 1, 5, 4, 6};
  vector<int> postorder = {1, 2, 4, 6, 5, 3};


  //unique_ptr<BinaryTreeNode<int> > tree(RebuildBSTFromPreorderFast(preorder));
  unique_ptr<BinaryTreeNode<int> > tree(RebuildBSTFromPostOrderFast(postorder));
  //CheckAns(tree, numeric_limits<int>::min());

  assert(3 == tree->data);
  assert(2 == tree->left->data);
  assert(1 == tree->left->left->data);
  assert(5 == tree->right->data);
  assert(4 == tree->right->left->data);
  assert(6 == tree->right->right->data);

  return 0;
}
