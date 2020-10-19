/*
* BinaryTreeNodesTotallyOrdered.cpp
* -----------------
*
* Chapter 15 Question 12
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

bool SearchTarget(unique_ptr<BinaryTreeNode<int> >& from, 
                  unique_ptr<BinaryTreeNode<int> >& target) {
  
  auto* iter = from.get();
  while (iter && iter != target.get()) {
    iter = iter->data < target->data ? iter->right.get() : iter->left.get();
  }
  return iter == target.get();
}

bool PairIncludesAncestorAndDescendantOfM(
  unique_ptr<BinaryTreeNode<int> >& possible_ans_or_desc1,
  unique_ptr<BinaryTreeNode<int> >& possible_ans_or_desc2,
  unique_ptr<BinaryTreeNode<int> >& middle
) {
  if (middle.get() == possible_ans_or_desc1.get() || middle.get() == possible_ans_or_desc2.get()) {
    return false;
  }

  auto* curr1 = possible_ans_or_desc1.get();
  auto* curr2 = possible_ans_or_desc2.get();
    
  while (curr1 != possible_ans_or_desc2.get() && curr2 != possible_ans_or_desc1.get() &&
          curr1 != middle.get() && curr2 != middle.get() && (curr1 || curr2)) {
    cout << "CURR 1 VAL BEFORE: " << curr1->data << endl;
    if (curr1) {
      curr1 = curr1->data < middle->data ? curr1 = curr1->right.get() : curr1->left.get();
    }

    cout << "CURR 1 VAL AFTER: " << curr1->data << endl;

    if (curr2) {
      curr2 = curr2->data < middle->data ? curr2 = curr2->right.get() : curr2->left.get();
    }
  }

  if ((curr1 != middle.get() && curr2 != middle.get()) || 
      curr1 == possible_ans_or_desc2.get() || curr2 == possible_ans_or_desc1.get()) {
        cout << (curr1) << endl;
        return false;
  }

  return curr1 == middle.get() ? 
            SearchTarget(middle, possible_ans_or_desc2) :
            SearchTarget(middle, possible_ans_or_desc1);

}

void SimpleTest() {
  auto root = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{5});
  assert(!PairIncludesAncestorAndDescendantOfM(root, root, root));
  root->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{2});
  root->left->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{4});
  assert(!PairIncludesAncestorAndDescendantOfM(root, root->left,
                                               root->left->right));
  assert(PairIncludesAncestorAndDescendantOfM(root, root->left->right,
                                              root->left));

  // Example of the first figure of BST chapter.
  root = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{19});
  root->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{7});
  root->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{3});
  root->left->left->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{2});
  root->left->left->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{5});
  root->left->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{11});
  root->left->right->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{17});
  root->left->right->right->left =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{13});
  root->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{43});
  root->right->left = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{23});
  root->right->left->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{37});
  root->right->left->right->left =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{29});
  root->right->left->right->left->right =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{31});
  root->right->left->right->right =
      make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{41});
  root->right->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{47});
  root->right->right->right = make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{53});

  assert(!PairIncludesAncestorAndDescendantOfM(root->right, root->left,
                                               root->right->left));
  assert(PairIncludesAncestorAndDescendantOfM(
      root, root->right->left->right->left->right, root->right->left));
}

int main(int argc, char** argv) {      
  
  SimpleTest();

  return 0;
}
