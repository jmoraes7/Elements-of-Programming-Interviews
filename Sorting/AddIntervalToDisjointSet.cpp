/*
* AddIntervalToDisjointSet.cpp
* -----------------
*
* Chapter 14 Question 6
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

struct Interval {
  int start, end;
};

bool isOverlapAlternative(Interval a, Interval b) {
  return std::min(a.end, b.end) < std::max(a.start, b.start);
}

bool isOverlap(Interval a, Interval b) {
  return a.start < b.end && b.start < a.end;
}

Interval getIntervalUnion(Interval a, Interval b) {
  Interval result{std::min(a.start, b.start), std::max(a.end, b.end)};
  return result;
}

vector<Interval> AddInterval(const vector<Interval>& disjoint_intervals, Interval new_interval) {
  vector<Interval> result;
  bool new_interval_added = false;

  for (int i = 0; i < disjoint_intervals.size(); i++) {
    Interval interval = disjoint_intervals[i];

    if (isOverlap(interval, new_interval)) {
      new_interval = getIntervalUnion(interval, new_interval); //Compute union
    } 
    
    else {
      if (new_interval.end < interval.start && !new_interval_added) {
        result.push_back(new_interval);
        new_interval_added = true;
      }

      result.push_back(interval);
    }
  }

  if (!new_interval_added) {
    result.push_back(new_interval);
  }
  
  return result;
}

int main(int argc, char** argv) {
  Interval a{-4, -1};
  Interval b{0, 2};
  Interval c{3, 6};
  Interval d{7, 9};
  Interval e{11, 12};
  Interval f{14, 17};
  
  Interval new_interval{1, 8};

  vector<Interval> intervals{a, b, c, d, e, f};

  //Interval x = getIntervalUnion(d, new_interval);

  for (Interval x : intervals) {
    cout << "(" << x.start << ", " << x.end << ")" << endl;
  }
  cout << endl;

  vector<Interval> result = AddInterval(intervals, new_interval);

  for (Interval x : result) {
    cout << "(" << x.start << ", " << x.end << ")" << endl;
  }
  return 0;
}
