/*
* CanBeBipartite.cpp
* -----------------
*
* Chapter 19 Question 7
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
  int d  = -1;
  vector<Vertex*> edges;
};

bool IsBipartite() {
  return false;
}

bool CanBeBipartite(Vertex* G) {

  queue<Vertex*> q;
  q.emplace(G);
  G->d = 1;

  while (!q.empty()) {
    auto v = q.front();
    for (auto e : v->edges) {
      if (e->d == -1) {
        e->d = v->d == 1 ? 0 : 1;
        q.emplace(e);
      } else {
        if (e->d == v->d) {
          return false;
        }
      }
    }
    q.pop();
  }

  return true;
}

void PrintGraph(Vertex* G) {
  cout << "GRAPH: " << endl;
  queue<Vertex*> q;
  q.emplace(G);
  unordered_set<Vertex*> visited;
  visited.insert(G);
  while (!q.empty()) {
    auto v = q.front();
    cout << v->d << endl;
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

  a.edges.push_back(&b);
  a.edges.push_back(&d);

  b.edges.push_back(&a);
  b.edges.push_back(&c);

  c.edges.push_back(&b);
  c.edges.push_back(&d);
  
  d.edges.push_back(&a);
  d.edges.push_back(&c);
  d.edges.push_back(&e);

  e.edges.push_back(&d);
    
  cout << boolalpha << CanBeBipartite(&a) << endl;
  //PrintGraph(&a);

  return 0;
}


