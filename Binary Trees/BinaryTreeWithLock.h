#ifndef BINARY_TREE_NODE_WITH_LOCK_H
#define BINARY_TREE_NODE__WITH_LOCK_H

#include <memory>

using namespace std;

// @include
class BinaryTreeNode {
  public:
    bool IsLocked() { return locked_; }

    bool Lock() {
      if (numDescendantsLocked > 0 || locked_) { 
        return false; 
      }

      //if ancestor is locked, return false
      for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
        if (iter->locked_) {
          return false;
        }
      }

      locked_ = true;
      for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
        iter->numDescendantsLocked++;
      }

      return true;
    }

    void Unlock() {
      locked_ = false;
      for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
        iter->numDescendantsLocked--;
      }
    }

    shared_ptr<BinaryTreeNode>& left() { return left_; }

    shared_ptr<BinaryTreeNode>& right() { return right_; }

    shared_ptr<BinaryTreeNode>& parent() { return parent_; }

  private:
    shared_ptr<BinaryTreeNode> left_, right_, parent_;
    int numDescendantsLocked = 0;
    bool locked_ = false;
};
// @exclude

#endif