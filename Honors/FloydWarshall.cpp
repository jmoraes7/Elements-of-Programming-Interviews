/*
* FloydWarshall.cpp
* -----------------
*
* Chapter 22 Question 49
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

struct HighwaySection {
  int x, y;
  double distance;
};

void FloydWarshall(vector<vector<double>>* G) {
  for (int k = 0; k < G->size(); k++) {
    for (int i = 0; i < G->size(); i++) {
      for (int j = 0; j < G->size(); j++) {
        if ((*G)[i][k] != std::numeric_limits<int>::max() &&
            (*G)[k][j] != std::numeric_limits<int>::max() && 
            (*G)[i][j] > (*G)[i][k] + (*G)[k][j]) {
          (*G)[i][j] = (*G)[i][k] + (*G)[k][j];
        }
      }
    }
  }
}

HighwaySection FindBestProposal(const vector<HighwaySection> H,
                                const vector<HighwaySection> P, int a, int b, int n) {
  vector<vector<double> > G(n, vector<double>(n, std::numeric_limits<double>::max()));
  for (int i = 0; i < n; i++) {
    G[i][i] = 0;
  }

  for (const HighwaySection& h : H) {
    G[h.x][h.y] = G[h.y][h.x] = h.distance;
  }

  FloydWarshall(&G);

  for (auto row : G) {
    for (int x : row) {
      cout << x << " ";
    }
    cout << endl;
  }

  HighwaySection best = {-1, -1, 0};
  double min_dist = G[a][b];
  for (const HighwaySection& p : P) {
    //check path a -> p.x -> p.y -> b
    if (G[a][p.x] != std::numeric_limits<double>::max() &&
        G[p.y][b] != std::numeric_limits<double>::max() &&
        min_dist > G[a][p.x] + p.distance + G[p.y][b]) {
      best = p;
      min_dist = G[a][p.x] + p.distance + G[p.y][b];
    }

    //check path a -> p.x -> p.y -> b
    if (G[a][p.y] != std::numeric_limits<double>::max() &&
        G[p.x][b] != std::numeric_limits<double>::max() &&
        min_dist > G[a][p.y] + p.distance + G[p.x][b]) {
      best = p;
      min_dist = G[a][p.x] + p.distance + G[p.y][b];
    }
  }

  return best;
}

int main(int argc, char** argv) {   

  vector<HighwaySection> H = {HighwaySection{0, 1, 5},
                              HighwaySection{1, 2, 7},
                              HighwaySection{1, 3, 10}};
  vector<HighwaySection> P = {HighwaySection{0, 3, 3},
                              HighwaySection{2, 3, 2},
                              HighwaySection{0, 2, 0.1}};

  HighwaySection t = FindBestProposal(H, P, 1, 3, 4);
  assert(t.x == 0 && t.y == 3 && t.distance == 3.0);

  return 0;
}


