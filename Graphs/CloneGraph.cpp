/*
* CloneGraph.cpp
* -----------------
*
* Chapter 19 Question 6
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
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
using std::stoul;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

struct Vertex {
  int label;
  vector<Vertex*> edges;
};

Vertex* CloneGraphBFS(Vertex* G) {
  if (!G) {
    return nullptr;
  }
  
  queue<Vertex*> q;
  q.emplace(G);

  unordered_map<Vertex*, Vertex*> node_to_clone;
  node_to_clone[G] = new Vertex({G->label});

  while (!q.empty()) {
    Vertex* node = q.front();
    for (const auto v : node->edges) {
      Vertex* clone;
      
      if (node_to_clone.find(v) == node_to_clone.end()) {
        node_to_clone[v] = new Vertex({v->label});
        q.emplace(v);
      }

      node_to_clone[node]->edges.push_back(node_to_clone[v]);
    }

    q.pop();
  }

  return node_to_clone[G];
}

void PrintGraph(Vertex* G) {
  cout << "GRAPH: " << endl;
  queue<Vertex*> q;
  q.emplace(G);
  unordered_set<Vertex*> visited;
  visited.insert(G);
  while (!q.empty()) {
    auto v = q.front();
    cout << v->label << endl;
    for (const auto child : v->edges) {
      if (!visited.count(child)) {
        visited.insert(child);
        q.emplace(child);
      }
    }

    q.pop();
  }
}

int main(int argc, char** argv) {   

  Vertex a{1}; 
  Vertex b{2}; 
  Vertex c{3}; 
  Vertex d{4}; 
  Vertex e{5}; 

  //a.edges.push_back(&b);
  a.edges.push_back(&c);
  a.edges.push_back(&d);

  //b.edges.push_back(&a);
  b.edges.push_back(&c);

  c.edges.push_back(&a);
  c.edges.push_back(&b);
  c.edges.push_back(&d);

  d.edges.push_back(&a);
  d.edges.push_back(&c);
  d.edges.push_back(&e);

  e.edges.push_back(&d);
  
  Vertex* clone = CloneGraphBFS(&a);
  
  PrintGraph(&a);

  PrintGraph(clone);

  return 0;
}


