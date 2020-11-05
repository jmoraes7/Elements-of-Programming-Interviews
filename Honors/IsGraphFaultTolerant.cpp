/*
* IsGraphFaultTolerant.cpp
* -----------------
*
* Chapter 22 Question 47
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::min;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

struct GraphVertex {
  char label;
  int l = std::numeric_limits<int>::max(), d = 0;
  vector<GraphVertex*> edges;
};

bool HasBridge(GraphVertex* cur, GraphVertex* pre, int time) {
  cur->d = ++time, cur->l = std::numeric_limits<int>::max();
  for (GraphVertex*& next : cur->edges) {
    if (next != pre) {
      cout << cur->label << " " << next->label << endl;
      cout << next->d << endl;
      if (next->d != 0) { //back edge - next was visited already
        cout << "BACK EDGE" << endl << endl;
        cur->l = std::min(cur->l, next->d);
      } else {
        cout << "Front EDGE" << endl << endl;

        if (!HasBridge(next, cur, time)) {
          return false;
        }
        cur->l = std::min(cur->l, next->l);
      }
    }
  }
  return (pre == nullptr || cur->l < cur->d);
}

bool isGraphFaultTolerant(vector<GraphVertex*>* G) {

  if (!G->empty()) {
    return HasBridge(G->front(), nullptr, 0);
  }
  return true;
}

int main(int argc, char** argv) {   

  GraphVertex a;
  a.label = 'a';

  GraphVertex b;
  b.label = 'b';

  GraphVertex c;
  c.label = 'c';

  a.edges.emplace_back(&b);
  a.edges.emplace_back(&c);

  b.edges.emplace_back(&a);
  b.edges.emplace_back(&c);

  c.edges.emplace_back(&a);
  c.edges.emplace_back(&b);

  vector<GraphVertex*> G;
  G.emplace_back(&a);
  G.emplace_back(&b);
  G.emplace_back(&c);

  cout << isGraphFaultTolerant(&G);

  return 0;
}


