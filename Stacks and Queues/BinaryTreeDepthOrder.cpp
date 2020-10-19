/*
* BinaryTreeDepthOrder.cpp
* -----------------
*
* Chapter 9 Question 9
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stdexcept>
#include <utility>
#include <random>

#include "./Binary_Tree_Prototype.h"

using namespace std;

using std::cout;
using std::default_random_engine;
using std::endl;
using std::istringstream;
using std::random_device;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

vector<vector<int> > BinaryTreeDepthOrder(const unique_ptr<BSTNode<int> >& node) {
  vector<vector<int> > result;

  queue<BSTNode<int>*> processing_nodes;
  processing_nodes.push(node.get());

  int num_nodes_at_curr_level = processing_nodes.size();
  vector<int> nodes_at_current_level;

  while (!processing_nodes.empty()) {
    auto curr = processing_nodes.front();
    processing_nodes.pop();
    --num_nodes_at_curr_level;

    if (curr) {
      nodes_at_current_level.push_back(curr->data);
      processing_nodes.push(curr->left.get());
      processing_nodes.push(curr->right.get());
    }

    if (num_nodes_at_curr_level == 0) {
      num_nodes_at_curr_level = processing_nodes.size();
      result.push_back(move(nodes_at_current_level));
    }
  }

  return result;
}

int main(int argc, char* argv[])
{  
  unique_ptr<BSTNode<int>> tree = make_unique<BSTNode<int>>(
      BSTNode<int>{3, nullptr, nullptr});
  tree->left = make_unique<BSTNode<int>>(
      BSTNode<int>{2, nullptr, nullptr});
  tree->left->left = make_unique<BSTNode<int>>(
      BSTNode<int>{1, nullptr, nullptr});
  tree->left->left->left = make_unique<BSTNode<int>>(
      BSTNode<int>{10, nullptr, nullptr});
  tree->left->left->left->right = make_unique<BSTNode<int>>(
      BSTNode<int>{13, nullptr, nullptr});
  tree->right = make_unique<BSTNode<int>>(
      BSTNode<int>{5, nullptr, nullptr});
  tree->right->left = make_unique<BSTNode<int>>(
      BSTNode<int>{4, nullptr, nullptr});
  tree->right->right = make_unique<BSTNode<int>>(
      BSTNode<int>{6, nullptr, nullptr});
  
  // should output 3
  //               2 5
  //               1 4 6
  //               10
  //               13

  vector<vector<int>> result = BinaryTreeDepthOrder(tree);
  vector<vector<int>> golden_res = {{3}, {2, 5}, {1, 4, 6}, {10}, {13}};

  for (int i = 0; i < result.size(); ++i) {
    for (int j = 0; j < result[i].size(); ++j) {
      cout << result[i][j] << "-" << golden_res[i][j] << endl;
    }
    cout << endl;
  }

  
  // assert(equal(golden_res.begin(), golden_res.end(), result.begin(),
  //             result.end()));

  return 0;
}