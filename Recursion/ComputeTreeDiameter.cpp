/*
* ComputeTreeDiameter.cpp
* -----------------
*
* Chapter 16 Question 11
*/

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_unique;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

// @include
struct TreeNode {
  struct Edge {
    unique_ptr<TreeNode> node;
    double length;
  };
  int x;
  vector<Edge> edges;
};

struct HeightAndDiameter {
  double height, diameter;
};

HeightAndDiameter ComputeHeightAndDiameter(const unique_ptr<TreeNode>& T) {
  double diameter = std::numeric_limits<double>::min();

  std::array<double, 2> max_heights = {0.0, 0.0};
  for (const auto& edge : T->edges) {
    HeightAndDiameter h_d = ComputeHeightAndDiameter(edge.node);
    
    int candidate_height = edge.length + h_d.height;
    if (candidate_height > max_heights[0]) {
      max_heights[1] = max_heights[0];
      max_heights[0] = candidate_height;
    } else if (candidate_height > max_heights[1]) {
      max_heights[1] = candidate_height;
    }

    diameter = std::max(diameter, h_d.diameter);
  }

  return HeightAndDiameter{max_heights[0], std::max(diameter, max_heights[0] + max_heights[1])};
}

double ComputeDiameter(const unique_ptr<TreeNode>& T) {
  return T ? ComputeHeightAndDiameter(T).diameter : 0.0;
}

int main(int argc, char* argv[]) {
  unique_ptr<TreeNode> r = nullptr;
  assert(0.0 == ComputeDiameter(r));
  r = make_unique<TreeNode>(TreeNode());

  r->edges.push_back(
      TreeNode::Edge{make_unique<TreeNode>(TreeNode()), 10});
  r->edges[0].node->edges.push_back(
      TreeNode::Edge{make_unique<TreeNode>(TreeNode()), 50});
  r->edges.push_back(
      TreeNode::Edge{make_unique<TreeNode>(TreeNode()), 20});
  assert(80 == ComputeDiameter(r));
  cout << ComputeDiameter(r) << endl;
  r->edges[0].node->edges.push_back(
      TreeNode::Edge{make_unique<TreeNode>(TreeNode()), 100});
  assert(150 == ComputeDiameter(r));
  cout << ComputeDiameter(r) << endl;
  return 0;
}