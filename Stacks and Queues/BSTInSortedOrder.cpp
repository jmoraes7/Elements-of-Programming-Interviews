/*
* BSTInSortedOrder.cpp
* -----------------
*
* Chapter 9 Question 5
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>

#include "./Binary_Tree_Prototype.h"

using namespace std;

using std::length_error;
using std::max;
using std::stack;

vector<int> BSTInSortedOrder(unique_ptr<BSTNode<int>>& tree) {
  vector<int> result; 
  const auto* curr = tree.get();
  stack<const BSTNode<int>*> s;

  while (!s.empty() || curr) {
    if (curr) {
      s.push(curr);
      //Going left
      curr = curr->left.get();
    } else {
      curr = s.top();
      s.pop();
      result.push_back(curr->data);

      //Going right
      curr = curr->right.get();
    }
  }

  return result;
}
void SimpleTest() {
  unique_ptr<BSTNode<int>> tree = make_unique<BSTNode<int>>(BSTNode<int>{43, nullptr});
      
  auto result = BSTInSortedOrder(tree);
  vector<int> golden_result = {43};
  assert(equal(golden_result.begin(), golden_result.end(), result.begin(),
               result.end()));

  tree->left = make_unique<BSTNode<int>>(BSTNode<int>{23, nullptr});
  result = BSTInSortedOrder(tree);
  golden_result = {23, 43};
  assert(equal(golden_result.begin(), golden_result.end(), result.begin(),
               result.end()));
}

int main()
{  
  SimpleTest();
  //        43
  //    23     47
  //      37      53
  //    29  41
  //     31
  unique_ptr<BSTNode<int>> tree = make_unique<BSTNode<int>>(BSTNode<int>{43, nullptr});
  tree->left = make_unique<BSTNode<int>>(BSTNode<int>{23, nullptr});
  tree->left->right = make_unique<BSTNode<int>>(BSTNode<int>{37, nullptr});
  tree->left->right->left =
      make_unique<BSTNode<int>>(BSTNode<int>{29, nullptr});
  tree->left->right->left->right =
      make_unique<BSTNode<int>>(BSTNode<int>{31, nullptr});
  tree->left->right->right =
      make_unique<BSTNode<int>>(BSTNode<int>{41, nullptr});
  tree->right = make_unique<BSTNode<int>>(BSTNode<int>{47, nullptr});
  tree->right->right = make_unique<BSTNode<int>>(BSTNode<int>{53, nullptr});
  
  auto result = BSTInSortedOrder(tree);
  vector<int> golden_res = {23, 29, 31, 37, 41, 43, 47, 53};

  assert(equal(golden_res.begin(), golden_res.end(), result.begin(),
               result.end()));

  // cout << BSTInSortedOrder() << endl;

  return 0;
}