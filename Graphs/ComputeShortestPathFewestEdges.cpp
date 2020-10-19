/*
* ComputeShortestPathFewestEdges.cpp
* -----------------
*
* Chapter 19 Question 11
*/

#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <set>
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
using std::set;
using std::stack;
using std::stoul;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

struct GraphVertex {
  std::pair<int, int> distance = {std::numeric_limits<int>::max(), 0};
  vector<std::pair<GraphVertex&, int> > edges;
  int id;
  const GraphVertex* pred = nullptr;
};

struct Comp {
  bool operator()(const GraphVertex* lhs, const GraphVertex* rhs) {
    return lhs->distance.first < rhs->distance.first || 
            (lhs->distance.first == rhs->distance.first &&
            lhs->distance.second < rhs->distance.second);
  }
};

void OutputShortestPath(const GraphVertex* t) {
  if (t) {
    OutputShortestPath(t->pred);
    cout << t->id << " ";
  }
}

void DijkstraShortestPath(GraphVertex* s, GraphVertex* t) {
  s->distance = {0, 0};
  set<GraphVertex*, Comp> nodes_to_visit;
  nodes_to_visit.emplace(s);

  while (!nodes_to_visit.empty()) {
    GraphVertex* u = *nodes_to_visit.begin();
    if (u->id == t->id) {
      break;
    }

    for (auto& e : u->edges) {
      int dist = u->distance.first + e.second;
      int num_edges = u->distance.second + 1;

      if (dist < e.first.distance.first ||
          (dist == e.first.distance.first && 
          num_edges < e.first.distance.second)) {
          
          nodes_to_visit.erase(&e.first);
          e.first.distance = {dist, num_edges};
          e.first.pred = u;
          nodes_to_visit.emplace(&e.first);
      }
    }
    nodes_to_visit.erase(u);
  }

  // output path;
  OutputShortestPath(t);
}

void Test() {
  vector<GraphVertex> G;
  for (int i = 0; i < 9; ++i) {
    G.emplace_back(GraphVertex());
    G[i].id = i;
  }

  // G[0] is the source node that connects to 8 other nodes.
  G[0].edges.push_back(std::pair<GraphVertex&, int>{G[1], 13});  // 0-1
  G[1].edges.push_back(std::pair<GraphVertex&, int>{G[0], 13});  // 1-0

  G[0].edges.push_back(std::pair<GraphVertex&, int>{G[2], 24});  // 0-2
  G[2].edges.push_back(std::pair<GraphVertex&, int>{G[0], 24});  // 2-0

  G[0].edges.push_back(std::pair<GraphVertex&, int>{G[3], 28});  // 0-3
  G[3].edges.push_back(std::pair<GraphVertex&, int>{G[0], 28});  // 3-0

  G[0].edges.push_back(std::pair<GraphVertex&, int>{G[4], 25});  // 0-4
  G[4].edges.push_back(std::pair<GraphVertex&, int>{G[0], 25});  // 4-0

  G[0].edges.push_back(std::pair<GraphVertex&, int>{G[5], 30});  // 0-5
  G[5].edges.push_back(std::pair<GraphVertex&, int>{G[0], 30});  // 5-0

  G[0].edges.push_back(std::pair<GraphVertex&, int>{G[6], 31});  // 0-6
  G[6].edges.push_back(std::pair<GraphVertex&, int>{G[0], 31});  // 6-0

  G[0].edges.push_back(std::pair<GraphVertex&, int>{G[7], 10});  // 0-7
  G[7].edges.push_back(std::pair<GraphVertex&, int>{G[0], 10});  // 7-0

  G[0].edges.push_back(std::pair<GraphVertex&, int>{G[8], 29});  // 0-8
  G[8].edges.push_back(std::pair<GraphVertex&, int>{G[0], 29});  // 8-0

  G[1].edges.push_back(std::pair<GraphVertex&, int>{G[8], 7});  // 1-8
  G[8].edges.push_back(std::pair<GraphVertex&, int>{G[1], 7});  // 8-1

  G[2].edges.push_back(std::pair<GraphVertex&, int>{G[8], 1});  // 2-8
  G[8].edges.push_back(std::pair<GraphVertex&, int>{G[2], 1});  // 8-2

  G[7].edges.push_back(std::pair<GraphVertex&, int>{G[8], 16});  // 7-8
  G[8].edges.push_back(std::pair<GraphVertex&, int>{G[7], 16});  // 8-7

  int s = 0;  // Source is G[0].
  int t = 2;  // Destination is G[2].

  // Minimum distance path should be:
  // G[0] => G[1] => G[8] => G[2],
  // distance is: 13 + 7 + 1 = 21.

  DijkstraShortestPath(&G[s], &G[t]);
  cout << endl
       << "Min distance: " << G[t].distance.first
       << endl;
  assert(G[t].distance.first == 21);
  cout << "Number of edges: " << G[t].distance.second
       << endl;
  assert(G[t].distance.second == 3);
}

int main(int argc, char** argv) {   
  Test();

  return 0;
}


