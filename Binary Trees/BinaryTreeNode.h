#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H

#include <memory>

using namespace std;

// @include
template <typename T>
struct BinaryTreeNode {
  T data;
  unique_ptr<BinaryTreeNode<T> > left, right;
  int size;
};
// @exclude

#endif
