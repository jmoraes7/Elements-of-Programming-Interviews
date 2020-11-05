/*
* FindClosestTwoPoints.cpp
* -----------------
*
* Chapter 22 Question 36
*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::get;
using std::numeric_limits;
using std::ostream;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

struct Point {
  int x, y;
};

struct PairOfPointsWithDistance { 
  Point p1, p2;
  double distance;
};

const int kBruteForceThreshold = 50;

double Distance(const Point& a, const Point& b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

PairOfPointsWithDistance SolveByEnumerateAllPairs(const vector<Point>& points, int start, int end) {
  
  PairOfPointsWithDistance res;
  res.distance = std::numeric_limits<double>::max();
  for (int i = start; i <= end; i++) {
    for (int j = start + 1; j <= end; j++) {
      double dist = Distance(points[i], points[j]); 
      if (dist < res.distance) {
        res = {points[i], points[j], dist};
      }
    }
  }

  return res;
}

PairOfPointsWithDistance FindClosestPairInRemain(vector<Point>& remain, double d) {
  sort(remain.begin(), remain.end(), 
        [](const Point& a, const Point& b) -> bool { return a.y < b.y; });
  // sort(points.begin(), points.end(),
  //     [](const Point& a, const Point& b) -> bool { return a.x < b.x; });

  //at most six points in remain
  PairOfPointsWithDistance res;
  res.distance = std::numeric_limits<double>::max();

  for (int i = 0; i < remain.size(); i++) {
    for (int j = i + 1; j < remain.size() && remain[j].y - remain[i].y < d; ++j) {
      double dist = Distance(remain[i], remain[j]);
      if (dist < res.distance) {
        res = {remain[i], remain[j], dist};
      }
    }
  }

  return res;
}

PairOfPointsWithDistance FindClosestPairPointsInSubarray(const vector<Point>& points, int start, int end ){
  PairOfPointsWithDistance res;

  if (end - start <= kBruteForceThreshold) {
    return SolveByEnumerateAllPairs(points, start, end);
  }

  int mid = start + ((end - start) / 2);

  auto left_res = FindClosestPairPointsInSubarray(points, start, mid);
  auto right_res = FindClosestPairPointsInSubarray(points, mid, end);
  auto best_res = left_res.distance < right_res.distance ? left_res : right_res;
  
  vector<Point> remain; //stores points whose x-dis < min_d
  for (const Point& p : points) {
    if (std::abs(p.x - points[mid].x) < best_res.distance) {
      remain.emplace_back(p);
    }
  }

  auto mid_res = FindClosestPairInRemain(remain, best_res.distance);

  return best_res.distance < mid_res.distance 
          ? best_res 
          : mid_res;
}

PairOfPointsWithDistance FindClosestPairPoints(vector<Point> points) {
  sort(points.begin(), points.end(),
      [](const Point& a, const Point& b) -> bool { return a.x < b.x; });

  auto closest_two_points = FindClosestPairPointsInSubarray(points, 0, points.size());

  return {closest_two_points.p1, closest_two_points.p2};
}

int main(int argc, char** argv) {   
  default_random_engine gen((random_device())());
  for (int times = 0; times < 50; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 5000);
      n = dis(gen);
    }
    cout << "num of points = " << n << endl;
    vector<Point> points;
    uniform_int_distribution<int> dis(0, 9999);
    for (int i = 0; i < n; ++i) {
      points.emplace_back(Point{dis(gen), dis(gen)});
    }
    auto p = FindClosestPairPoints(points);
    //auto q = SolveByEnumerateAllPairs(points, 0, points.size());
    // cout << "p = " << p.p1 << " " << p.p2
    //      << ", dis = " << Distance(p.p1, p.p2) << endl;
    // cout << "q = " << q.p1 << " " << q.p2
    //      << ", dis = " << Distance(q.p1, q.p2) << endl;
    //assert(Distance(p.p1, p.p2) == q.distance);
  }

  return 0;
}


