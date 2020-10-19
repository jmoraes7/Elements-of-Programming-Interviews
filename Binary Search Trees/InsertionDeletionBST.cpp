/*
* InsertionDeletionBST.cpp
* -----------------
*
* Chapter 15 Question 11
*/
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

class BinarySearchTree {
  public:
    bool Insert(int key) {
      if (root_ == nullptr) {
        root_ = make_unique<BinaryTreeNode<int> >(BinaryTreeNode<int>{
          key, nullptr, nullptr
        });
      } else {

        BinaryTreeNode<int> *curr = root_.get(), *parent = nullptr;
        while (curr) {
          parent = curr;
          if (curr->data > key) {
            curr = curr->left.get();
          } else if (curr->data < key) {
            curr = curr->right.get();
          } else {
            return false; 
          }
        }

        auto new_node = new BinaryTreeNode<int>{key, nullptr, nullptr};
          
        cout << "PARENT: " << parent->data << " KEY: " << key << endl;

        if (key < parent->data) {
          parent->left.reset(new_node);
        } else { 
          parent->right.reset(new_node);
        }
      }

      return true;
    }

    bool Delete(int key) {
      if (root_ == nullptr) { return false; }

      BinaryTreeNode<int> *curr = root_.get(), *parent = nullptr;

      while (curr && curr->data != key) {
        parent = curr;
        curr = curr->data < key ? curr->right.get() : curr->left.get();
      }

      if (curr == nullptr) { // key not in BST
        return false;
      }

      if (curr->right != nullptr) {
        auto *r_key_curr = curr->right.get(), *r_key_parent = curr;

        while (r_key_curr->left != nullptr) { //get curr successor node
          r_key_parent = r_key_curr;
          r_key_curr = r_key_curr->left.get();
        }

        curr->data = r_key_curr->data;

        if (r_key_curr == r_key_parent->right.get()) {
          r_key_parent->right.reset(r_key_curr->right.release());
        } else {
          r_key_parent->left.reset(r_key_curr->right.release());
        }
      } else {
        if (root_.get() == curr) {
          root_.reset(curr->left.release());
        } else {
          if (parent->left.get() == curr) {
            parent->left.reset(curr->left.release());
          } else {
            parent->right.reset(curr->left.release());
          }
        }
      }
      
      return true;
    }

    bool Empty() {
      return root_ == nullptr;
    }

    int getRootVal() {
      return root_->data;
    }

  private:
    unique_ptr<BinaryTreeNode<int> > root_ = nullptr;
};

int main(int argc, char** argv) {      
  BinarySearchTree BST;
  assert(BST.Empty() == true);
  assert(BST.Insert(7) == true);
  assert(BST.Insert(8) == true);
  assert(BST.Insert(9) == true);
  assert(BST.Insert(4) == true);
  assert(BST.Insert(3) == true);
  assert(BST.Empty() == false);
  assert(BST.Insert(2) == true);
  assert(BST.Insert(5) == true);
  assert(BST.Delete(7) == true);
  assert(BST.Delete(9) == true);
  //assert(BST.Delete(8) == true);
  
  cout << BST.getRootVal() << endl;
  return 0;
}
