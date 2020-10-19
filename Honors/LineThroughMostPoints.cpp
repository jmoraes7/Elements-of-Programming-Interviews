/*
* LineThroughMostPoints.cpp
* -----------------
*
* Chapter 22 Question 22
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::greater;
using std::hash;
using std::istringstream;
using std::length_error;
using std::make_shared;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::stringstream;
using std::stoi;
using std::unordered_map;
using std::unordered_set;
using std::vector;

int GCD(int x, int y) {
  if (x == 0) {
    return y;
  } else if (y == 0) {
    return x;
  } else if (!(x & 1) && !(y & 1)) { // x and y both even
    return GCD(x >> 1, y >> 1) << 1;
  } else if (!(x & 1) && (y & 1)) { // x is even, y is odd
    return GCD(x >> 1, y);
  } else if ((x & 1) && !(y & 1)) { // x is odd, y is even
    return GCD(x, y >> 1);
  } else if (x > y) {                          // x and y are both odd; 
    return GCD(x - y, y);
  }
  return GCD(x, y - x);
}

struct Point {
  //equal function for hash
  bool operator==(const Point& that) const {
    return x == that.x && y == that.y;
  } 

  int x, y;
};

struct HashPoint {
  size_t operator()(const Point& p) const{
    return hash<int>()(p.x) ^ hash<int>()(p.y);
  }
};

struct Rational {
  bool operator==(const Rational& that) const {
    return numerator == that.numerator && denominator == that.denominator;
  }
  int numerator, denominator;
};

Rational GetCanonicalForm(int a, int b) {
  int gcd = GCD(abs(a), (abs(b)) );
  a /= gcd, b /= gcd;
  return b < 0 ? Rational{-a, -b} : Rational{a, b};
};

struct Line {
  Line(const Point& a, const Point& b) {
    slope = a.x != b.x ? 
            GetCanonicalForm(b.y - a.y, b.x - a.x) : 
            Rational{1, 0};
    intercept = a.x != b.x ? 
                GetCanonicalForm(b.x * a.y - b.y * a.x, b.x - a.x) :
                Rational{a.x, 1};
  }
  
  bool operator==(const Line& that) const {
    return slope == that.slope && intercept == that.intercept;
  }

  Rational slope, intercept;
};

struct HashLine {
  size_t operator()(const Line& l) const {
    return hash<int>()(l.slope.numerator) ^ 
            hash<int>()(l.slope.denominator) ^
            hash<int>()(l.intercept.numerator) ^ 
            hash<int>()(l.intercept.denominator);
  }
};

Line LineThroughMostPoints(const vector<Point>& P) {
  unordered_map<Line, unordered_set<Point, HashPoint>, HashLine> table;

  for (int i = 0; i < P.size(); i++) {
    for (int j = i + 1; j < P.size(); j++) {
      Line line(P[i], P[j]);
      table[line].insert(P[i]);
      table[line].insert(P[j]);
    }
  }

  int max_size = 0;
  Point p{-1, -1};
  Point q{0, 0};
  Line line_result(p, q);
  for (auto& line_set : table) {
    int line_point_set_size = line_set.second.size();
    if (line_point_set_size > max_size) {
      max_size = line_point_set_size;
      line_result = line_set.first; 
    }
    cout << line_set.second.size() << endl;
  }

  return line_result;
}

int main(int argc, char** argv) {   

  Point p{1, 2};
  Point q{2, 4};
  Point r{-1, -2};
  Point s{-4, -2};

  double m = ((double) (p.y - q.y)) / ((double)  (p.x - q.x));


  double b = p.y - p.x * m;
  
  vector<Point> points;
  points.emplace_back(p);
  points.emplace_back(q);
  points.emplace_back(r);
  points.emplace_back(s);

  Line line = LineThroughMostPoints(points);

  cout << "SLOPE: " << line.slope.numerator << "/" << line.slope.denominator << " Intercept: " 
        << line.intercept.numerator << "/" << line.intercept.denominator;
  
  //m = (y2 - y1) / (x2 - x1)

  //b = y2 - (m * (x2 - x1)) -> (y1*x2 - y2*x1) / (x2 - x1)

  return 0;
}


