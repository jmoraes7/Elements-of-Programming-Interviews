#ifndef BINARY_TREE_PROTOTYPE_H
#define BINARY_TREE_PROTOTYPE_H

#include <memory>

using namespace std;

using std::shared_ptr;

// @include
template <typename T>
struct BSTNode {
  T data;
  unique_ptr<BSTNode<T>> left, right;
};
// @exclude

#endif
