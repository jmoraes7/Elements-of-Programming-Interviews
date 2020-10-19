/*
* IntervalCovering.cpp
* -----------------
*
* Chapter 18 Question 4
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

struct Interval {
  public: 
    bool operator<(const Interval& that) const {
      return end < that.end;
    }
    
    int start, end, idx;
};

struct Endpoint {
  bool operator<(const Endpoint& that) const {
    int a = is_left ? ptr->start : ptr->end;
    int b = that.is_left ? that.ptr->start : that.ptr->end;
    return a <= b || (a == b && is_left && !that.is_left);
  }
  const Interval* ptr;
  bool is_left;
};


vector<int> FindMinimumVisitsHelper(const vector<Endpoint>& endpoints) {
  vector<int> result;
  unordered_set<int> covered;
  vector<int> covering;

  for (const auto& e : endpoints) {
    if (e.is_left) {
      covering.emplace_back(e.ptr->idx);
    } else if (!covered.count(e.ptr->idx)) {
      result.push_back(e.ptr->end);

      covered.insert(covering.begin(), covering.end());
      covering.clear();
    }
  }

  return result;
}

vector<int> FindMinimumVisitsInefficient(vector<Interval>& I) {
  vector<Endpoint> endpoints;

  for (size_t i = 0; i < I.size(); i++) {
    endpoints.push_back(Endpoint{&I[i], true});
    endpoints.push_back(Endpoint{&I[i], false});
  }

  sort(endpoints.begin(), endpoints.end());

  return FindMinimumVisitsHelper(endpoints);
}

vector<int> FindMinimumVisits(vector<Interval> I) {
  if (I.empty()) {
    return {};
  }

  std::sort(I.begin(), I.end());
  
  vector<int> visiting_times;

  int curr_overlapping_point = I[0].end;
  for (int i = 1; i < I.size(); i++) {
  
    if (I[i].start > curr_overlapping_point) {
      visiting_times.push_back(curr_overlapping_point);

      curr_overlapping_point = I[i].end;
    }    
  }

  visiting_times.push_back(curr_overlapping_point);

  return visiting_times;
}

int main(int argc, char** argv) {   
  
  vector<Interval> intervals;
  intervals.emplace_back(Interval{0, 3, 0});
  intervals.emplace_back(Interval{2, 6, 1});
  intervals.emplace_back(Interval{3, 4, 2});
  intervals.emplace_back(Interval{6, 9, 3});
  // intervals.emplace_back(Interval{7, 8, 4});
  // intervals.emplace_back(Interval{7,7, 5});


  vector<Interval> intervals2;
  intervals2.emplace_back(Interval{1, 2, 0});
  intervals2.emplace_back(Interval{2, 3, 1});
  intervals2.emplace_back(Interval{3, 4, 2});
  intervals2.emplace_back(Interval{2, 3, 3});
  intervals2.emplace_back(Interval{3, 4, 4});
  intervals2.emplace_back(Interval{4, 5, 5});

  vector<int> visit_times = FindMinimumVisitsInefficient(intervals2);

  for (int time : visit_times) {
    cout << time << " ";
  }

  return 0;
}


