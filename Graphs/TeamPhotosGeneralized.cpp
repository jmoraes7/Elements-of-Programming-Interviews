/*
* TeamPhotoGeneralized.cpp
* -----------------
*
* Chapter 19 Question 10
*/

#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::array;
using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::random_device;
using std::stack;
using std::stoul;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

struct Vertex {
  int label = 0;
  vector<Vertex*> edges; 
  int max_distance = 1;
  bool visited = false;
};

void DFS(Vertex* cur, stack<Vertex*>* vertex_order) {
  cur->visited = true;
  for (auto& v : cur->edges) {
    if (!v->visited) {
      DFS(v, vertex_order);
    }
  }
  vertex_order->emplace(cur);
}

stack<Vertex*> BuildTopologicalOrdering(vector<Vertex>* G) {
  stack<Vertex*> vertex_order;
  for (auto& g : *G) {
    if (!g.visited) {
      DFS(&g, &vertex_order);
    }
  }
  return vertex_order;
}

int FindLongestPath(stack<Vertex*>* vertex_order) {
  int max_dist = 0;
  while (!vertex_order->empty()) {
    Vertex* u = vertex_order->top();
    max_dist = std::max(max_dist, u->max_distance);
    for (auto& v : u->edges) {
      v->max_distance = std::max(v->max_distance, u->max_distance + 1);
    }
    vertex_order->pop();
  }
  return max_dist;
}

int FindLargestNumberTeams(vector<Vertex>* G) {
  stack<Vertex*> vertex_order(BuildTopologicalOrdering(G));
  return FindLongestPath(&vertex_order);
}


int main(int argc, char** argv) {   
  vector<Vertex> G(3);
  G[0].label = 1;
  G[1].label = 2;
  G[2].label = 3;
  G[0].edges.emplace_back(&G[2]);
  G[1].edges.emplace_back(&G[2]);
  assert(2 == FindLargestNumberTeams(&G));

  return 0;

}


