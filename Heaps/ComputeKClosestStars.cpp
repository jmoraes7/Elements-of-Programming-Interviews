/*
* ComputeKClosestStars.cpp
* -----------------
*
* Chapter 11 Question 4
*/

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

static vector<int> result;

struct Star {
  public:
    bool operator<(const Star& rhs) const {
      double distance = x * x + y * y + z * z;
      double rhs_distance = rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z;
      return distance < rhs_distance; //max heap 
    }

    double Distance() { return x * x + y * y + z * z; }

    double x, y, z;
};

vector<Star> FindClosestKStars(int k, istringstream* stars) {
  priority_queue<Star, vector<Star> > max_heap;
  vector<Star> closest_stars;

  string line;
  while (getline(*stars, line)) {
    stringstream line_stream(line);
    array<double, 3> data; // stores x, y and z
    for (int i = 0; i < 3; ++i) {
      string buf;
      getline(line_stream, buf, ',');
      data[i] = stod(buf);
    }

    max_heap.push(Star{data[0], data[1], data[2]});
    if (max_heap.size() == k+1) {
      max_heap.pop();
    }
  }

  while (!max_heap.empty()) {
    closest_stars.push_back(max_heap.top());
    max_heap.pop();
  }
  
  reverse(closest_stars.begin(), closest_stars.end());

  return closest_stars;
}

string CreateStreamingString(const vector<Star>& stars) {
  string s;
  for (int i = 0; i < stars.size(); ++i) {
    stringstream ss;
    ss << stars[i].x << ',' << stars[i].y << ',' << stars[i].z << endl;
    s += ss.str();
  }
  return s;
}

void SimpleTest() {
  vector<Star> stars;
  stars.push_back((Star{1, 2, 3}));
  stars.push_back((Star{5, 5, 5}));
  stars.push_back((Star{0, 2, 1}));
  stars.push_back((Star{9, 2, 1}));
  stars.push_back((Star{1, 2, 1}));
  stars.push_back((Star{2, 2, 1}));
  istringstream sin(CreateStreamingString(stars));
  vector<Star> closest_stars = FindClosestKStars(3, &sin);
  assert(3 == closest_stars.size());
  assert(closest_stars[0].Distance() == (Star{0, 2, 1}.Distance()));
  assert(closest_stars[0].Distance() == (Star{2, 0, 1}.Distance()));
  assert(closest_stars[1].Distance() == (Star{1, 2, 1}.Distance()));
  assert(closest_stars[1].Distance() == (Star{1, 1, 2}.Distance()));

  stars.clear();
  stars.push_back((Star{1, 2, 3}));
  stars.push_back((Star{5, 5, 5}));
  stars.push_back((Star{4, 4, 4}));
  stars.push_back((Star{3, 2, 1}));
  stars.push_back((Star{5, 5, 5}));
  stars.push_back((Star{3, 2, 3}));
  stars.push_back((Star{3, 2, 3}));
  stars.push_back((Star{3, 2, 1}));
  istringstream sin2(CreateStreamingString(stars));
  closest_stars = FindClosestKStars(2, &sin2);
  assert(2 == closest_stars.size());
  assert(closest_stars[0].Distance() == (Star{1, 2, 3}.Distance()));
  assert(closest_stars[1].Distance() == (Star{3, 2, 1}.Distance()));
}

int main(int argc, char* argv[]) {
  SimpleTest();

  return 0;
}