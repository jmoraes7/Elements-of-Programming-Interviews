/*
* DoesArbitrageExist.cpp
* -----------------
*
* Chapter 22 Question 50
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::min;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;

struct GraphVertex {
  char label;
  unordered_map<GraphVertex*, int> edges;
};

bool BellmanFord(const vector<vector<double>>& G, int source) {
  vector<double> dis_to_source(G.size(), std::numeric_limits<double>::max());
  dis_to_source[source] = 0;

  for (size_t times = 1; times < G.size(); times++) {
    bool have_update = false;
    for (size_t i = 0; i < G.size(); i++) {
      for (size_t j = 0; j < G.size(); j++) { //loop through edges
        if (dis_to_source[i] != std::numeric_limits<double>::max() &&
            dis_to_source[j] > dis_to_source[i] + G[i][j]) {
              have_update = true;
              dis_to_source[j] = dis_to_source[i] + G[i][j];
            }
      }
    }

    if (have_update == false) { //no update means no negative cycle
      return false;
    }
  }

  for (size_t i = 0; i < G.size(); ++i) {
    for (size_t j = 0; j < G.size(); ++j) {
      if (dis_to_source[i] != std::numeric_limits<double>::max() && 
          dis_to_source[j] > dis_to_source[i] + G[i][j]) {
            //there is further update to be made
            return true;
          }
    }
  }

  return false;
}

bool DoesArbitrageExist(vector<vector<double>> G) {
  for (vector<double>& edge_list : G) {
    for (double& edge : edge_list) {
      edge = -log10(edge);
    }
  }

  return BellmanFord(G, 0); //can use vertex as source since graph is complete
}

int main(int argc, char** argv) {   
  vector<vector<double>> g(3, vector<double>(3));
  for (size_t i = 0; i < 3; ++i) {
    g[i][i] = 1;
  }
  g[0][1] = 2, g[1][0] = 0.5, g[0][2] = g[2][0] = 1, g[1][2] = 4,
  g[2][1] = 0.25;
  bool res = DoesArbitrageExist(g);
  assert(res == true);

  return 0;
}


