/*
* UnionOfIntervals.cpp
* -----------------
*
* Chapter 14 Question 7
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

struct Endpoint{
  bool isClosed;
  int val;
};

struct Interval {  
  public:
    // bool operator<(const Interval& i) const {
    //   return left.val != i.left.val ? left.val < i.left.val : (left.isClosed && !i.left.isClosed);
    // }

    // Endpoint left, right;
    bool operator<(const Interval& i) const {
      return left < i.left;
    }
    int left, right;
};

// bool isOverlap(Interval a, Interval b) {
//   bool leftCompare = a.left.val < b.right.val ? 
//                       true : 
//                       (a.left.val == b.right.val) ? 
//                           (a.left.isClosed || b.right.isClosed) : 
//                           false;

//   bool rightCompare = b.left.val < a.right.val ?
//                        true : 
//                        (b.left.val == a.right.val) ?
//                         (b.left.isClosed || a.right.isClosed) :
//                         false;

//   // cout << "LEFT COMPARE: " << a.left.val << " " << b.right.val << " " << leftCompare << endl;
//   // cout << "Right COMPARE: " << b.left.val << " " << a.right.val << " " << rightCompare << endl;

//   return leftCompare && rightCompare;
// }

// Interval getIntervalUnion(Interval a, Interval b) {
//   Interval min_left = a.left.val < b.left.val ? a : b;
//   bool isLeftClosed = a.left.val == b.left.val ? (a.left.isClosed || b.left.isClosed) : min_left.left.isClosed;
  
//   Interval max_right = a.right.val > b.right.val ? a : b;
//   bool isRightClosed = a.right.val == b.right.val ? (a.right.isClosed || b.right.isClosed) : max_right.right.isClosed;;

//   Endpoint left{isLeftClosed, min_left.left.val};
//   Endpoint right{isRightClosed, max_right.right.val};
  
//   Interval result{left, right};
  
//   return result;
// }

// vector<Interval> getUnionOfIntervals(vector<Interval>& intervals) {
//   vector<Interval> disjoint_union;

//   std::sort(intervals.begin(), intervals.end());
//   Interval curr = intervals.front();

//   for (int i = 1; i < intervals.size(); ++i) {
//     Interval interval = intervals[i]; 
//     if (isOverlap(curr, intervals[i])) {
//       curr = getIntervalUnion(curr, intervals[i]);
//     } else {
//       disjoint_union.push_back(curr);
//       curr = intervals[i];
//     }
//   }
  
//   disjoint_union.push_back(curr);

//   return disjoint_union;
// }

int main(int argc, char** argv) {
  // Interval a{Endpoint{false, 0}, Endpoint{false, 3}};
  // Interval b{Endpoint{true, 1}, Endpoint{true, 1}};
  // Interval c{Endpoint{true, 2}, Endpoint{true, 4}};
  // Interval d{Endpoint{true, 3}, Endpoint{false, 4}};
  // Interval e{Endpoint{true, 5}, Endpoint{false, 7}};
  // Interval f{Endpoint{true, 7}, Endpoint{false, 8}};
  // Interval g{Endpoint{true, 8}, Endpoint{false, 11}};
  // Interval h{Endpoint{false, 9}, Endpoint{true, 11}};
  // Interval i{Endpoint{true, 12}, Endpoint{true, 14}};
  // Interval j{Endpoint{false, 12}, Endpoint{true, 16}};
  // Interval k{Endpoint{false, 13}, Endpoint{false, 15}};
  // Interval l{Endpoint{false, 16}, Endpoint{false, 17}};

  // vector<Interval> intervals{a, b, c, d, e, f, g, h, i, j, k, l};

  // for (Interval x : intervals) {
  //   cout << "(" << x.left.val << ", " << x.right.val << ")" << endl;
  // }
  // cout << endl;

  // vector<Interval> result = getUnionOfIntervals(intervals);

  // for (Interval x : result) {
  //   cout << "(" << x.left.val << ", " << x.right.val << ")" << endl;
  // }

  vector<Interval> intervals;
  intervals.push_back(Interval{1,3});
  intervals.push_back(Interval{0,2});

  sort(intervals.begin(), intervals.end());

  
  
  return 0;
}
