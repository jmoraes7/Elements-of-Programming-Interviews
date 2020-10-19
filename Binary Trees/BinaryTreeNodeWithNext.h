#ifndef BINARY_TREE_NODE_WITH_NEXT_H
#define BINARY_TREE_NODE__WITH_NEXT_H

#include <memory>

using namespace std;

// @include
template <typename T>
struct BinaryTreeNode {
  T data;
  shared_ptr<BinaryTreeNode<T> > left, right, next;
};
// @exclude

#endif
