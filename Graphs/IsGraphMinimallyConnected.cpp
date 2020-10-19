/*
* IsGraphMinimallyConnected.cpp
* -----------------
*
* Chapter 19 Question 5
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
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
using std::vector;

struct Vertex {
  char c;
  enum Color {white, gray, black} color;
  vector<Vertex*> edges;
};

bool HasCycle(Vertex* cur, const Vertex* pre) {
  if (cur->color == Vertex::gray) {
    return true;
  }

  cur->color = Vertex::gray;
  for (Vertex* next : cur->edges) {
    if (next != pre && next->color != Vertex::black) {
      if (HasCycle(next, cur)) {
        return true;
      }
    }
  }
  cur->color = Vertex::black;

  return false;
}

bool IsGraphMinimallyConnected(vector<Vertex>* G) {
  if (!G->empty()) {
    return !HasCycle(&G->front(), nullptr);   
  }
  return true;
}

int main(int argc, char** argv) {   

  Vertex a{'a', Vertex::white}; 
  Vertex b{'b', Vertex::white}; 
  Vertex c{'c', Vertex::white}; 
  Vertex d{'d', Vertex::white}; 
  Vertex e{'e', Vertex::white}; 
  Vertex f{'f', Vertex::white}; 
  Vertex g{'g', Vertex::white}; 
  Vertex h{'h', Vertex::white}; 
  Vertex i{'i', Vertex::white}; 
  Vertex j{'j', Vertex::white}; 
  Vertex k{'k', Vertex::white}; 
  Vertex l{'l', Vertex::white}; 
  Vertex m{'m', Vertex::white}; 

  a.edges.push_back(&b);
  //a.edges.push_back(&c); //uncomment to get a non-minimally connected graph

  b.edges.push_back(&a);
  b.edges.push_back(&e);

  c.edges.push_back(&d);

  d.edges.push_back(&c);
  d.edges.push_back(&e);

  e.edges.push_back(&b);
  e.edges.push_back(&d);
  e.edges.push_back(&f);
  e.edges.push_back(&h);

  f.edges.push_back(&e);
  f.edges.push_back(&g);
  f.edges.push_back(&i);

  g.edges.push_back(&f);

  h.edges.push_back(&e);

  i.edges.push_back(&f);
  i.edges.push_back(&j);
  i.edges.push_back(&m);
 
  j.edges.push_back(&i);

  k.edges.push_back(&m);
  k.edges.push_back(&l);

  l.edges.push_back(&k);

  m.edges.push_back(&i);
  m.edges.push_back(&k);

  vector<Vertex> G{a, b, c, d, e, f, g, h, i, j, k, l, m};

  cout << boolalpha << IsGraphMinimallyConnected(&G) << endl;

  return 0;
}


