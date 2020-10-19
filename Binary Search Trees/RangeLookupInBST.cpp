/*
* BinaryTreeNodesTotallyOrdered.cpp
* -----------------
*
* Chapter 15 Question 13
*/
#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <memory>
#include <map>
#include <set>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::set;
using std::unique_ptr;
using std::vector;

void RangeLookupHelper(unique_ptr<BinaryTreeNode<int> >& tree,
            const std::pair<int, int>& interval,
            vector<int>* result) {
  if (tree == nullptr) {
    return;
  }

  if (tree->data < interval.first) {
    RangeLookupHelper(tree->right, interval, result);
  } else if (tree->data > interval.second) {
    RangeLookupHelper(tree->left, interval, result);
  } else {
    (*result).push_back(tree->data);
    RangeLookupHelper(tree->left, interval, result);
    RangeLookupHelper(tree->right, interval, result);
  }
}

vector<int> RangeLookup(unique_ptr<BinaryTreeNode<int> >& tree, const std::pair<int, int>& interval) {
  vector<int> result;
  RangeLookupHelper(tree, interval, &result);
  return result;
}

int main(int argc, char** argv) {   
  //          19
  //     7          43
  //   3   11    23   47
  // 2  5    17   37    53
  //        13  29  41
  //             31
  unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{19});
  tree->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{7});
  tree->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{3});
  tree->left->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{2});
  tree->left->left->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{5});
  tree->left->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{11});
  tree->left->right->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{17});
  tree->left->right->right->left =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{13});
  tree->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{43});
  tree->right->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{23});
  tree->right->left->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{37});
  tree->right->left->right->left =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{29});
  tree->right->left->right->left->right =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{31});
  tree->right->left->right->right =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{41});
  tree->right->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{47});
  tree->right->right->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{53});
  auto result = RangeLookup(tree, {16, 31});
  sort(result.begin(), result.end());
  vector<int> golden_result = {17, 19, 23, 29, 31};
  assert(equal(result.begin(), result.end(), golden_result.begin(),
               golden_result.end()));

  result = RangeLookup(tree, {38, 39});
  assert(0 == result.size());

  result = RangeLookup(tree, {38, 42});
  assert((1 == result.size()) && (41 == result[0]));

  result = RangeLookup(tree, {-1, 1});
  assert(0 == result.size());

  result = RangeLookup(
      tree, {numeric_limits<int>::max() - 1, numeric_limits<int>::max()});
  assert(0 == result.size());
  
  return 0;
}
