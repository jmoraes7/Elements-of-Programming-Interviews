/*
* CalculateViewFromAbove.cpp
* -----------------
*
* Chapter 22 Question 30
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::equal;
using std::make_unique;
using std::map;
using std::unique_ptr;
using std::vector;
using std::unordered_set;

struct LineSegment {
  int left, right;
  int color;
  int height;
};

class Endpoint { 
  public:
    bool operator<(const Endpoint& that) const { 
      return Value() < that.Value();
    }

    int Value() const { return isLeft_ ? line_->left : line_->right; }

    const LineSegment* line_;
    bool isLeft_;
}; 

vector<LineSegment> CalculateViewFromAbove(const vector<LineSegment>& A) {
  vector<Endpoint> endpoints;

  for (const LineSegment& line : A) {
    endpoints.emplace_back(Endpoint{&line, true});
    endpoints.emplace_back(Endpoint{&line, false});
  }
  sort(endpoints.begin(), endpoints.end());

  int prev_xaxis = endpoints.front().Value();
  unique_ptr<LineSegment> prev = nullptr;
  map<int, const LineSegment*> lines_being_processed;
  vector<LineSegment> result;
  for (const Endpoint& endpoint : endpoints) {
    if (!lines_being_processed.empty() && prev_xaxis != endpoint.Value()) {
      if (prev == nullptr) { //looking at first endpoint
        prev = make_unique<LineSegment>(
                  LineSegment{
                    prev_xaxis, endpoint.Value(), lines_being_processed.crbegin()->second->color, lines_being_processed.crbegin()->second->height
                  }
                );
      }
      else {
        if (prev->height == lines_being_processed.crbegin()->second->height &&
            prev->color == lines_being_processed.crbegin()->second->color && prev_xaxis == prev->right) {
              prev->right = endpoint.Value();
        } else {
          result.emplace_back(*prev);
          *prev = {prev_xaxis, endpoint.Value(),
                    lines_being_processed.crbegin()->second->color, lines_being_processed.crbegin()->second->height };
        }
      }
      // cout << prev->left << " " << prev->right << " " << prev->color << " " << prev->height << endl;
    }    

    //prev_axis = 5
    //prev = {5, 5, 3, 1}
    // LineSegment{0, 4, 0, 0},     (LineSegment{1, 3, 1, 2}),
    //   (LineSegment{2, 7, 2, 0}),   (LineSegment{4, 5, 3, 3}),
    //   (LineSegment{5, 7, 3, 1}),   (LineSegment{6, 10, 0, 2}),

    prev_xaxis = endpoint.Value();

    if (endpoint.isLeft_) {
      lines_being_processed[endpoint.line_->height] = endpoint.line_;
    } else {
      lines_being_processed.erase(endpoint.line_->height);
    }
  }

  if (prev) {
    result.emplace_back(*prev);
  }
  
  cout << "RESULT" << endl;
  for (auto segment : result) {
    cout << "Start: " << segment.left << " End: " << segment.right << " Color: " << segment.color << " Height: " << segment.height << endl;
  }
  cout << endl << endl;

  return result;
}

void SimpleTest() {
  vector<LineSegment> A = {LineSegment{1, 2, 0, 1}, LineSegment{3, 4, 0, 1}};
  auto result = CalculateViewFromAbove(A);
  vector<LineSegment> golden_result = {LineSegment{1, 2, 0, 1},
                                       LineSegment{3, 4, 0, 1}};
  assert(equal(result.begin(), result.end(), golden_result.begin(),
               golden_result.end(),
               [](const LineSegment& a, const LineSegment& b) {
                 return a.left == b.left && a.right == b.right &&
                        a.color == b.color && a.height == b.height;
               }));
}

int main(int argc, char** argv) {   
  cout << "SIMPLE TEST: " << endl;
  SimpleTest();
  vector<LineSegment> A = {
      LineSegment{0, 4, 0, 0},     (LineSegment{1, 3, 1, 2}),
      (LineSegment{2, 7, 2, 1}),   (LineSegment{4, 5, 3, 3}),
      (LineSegment{5, 7, 3, 0}),   (LineSegment{6, 10, 0, 2}),
      (LineSegment{8, 9, 0, 1}),   (LineSegment{9, 18, 4, 0}),
      (LineSegment{11, 13, 3, 2}), (LineSegment{12, 15, 4, 1}),
      (LineSegment{14, 15, 2, 2}), (LineSegment{16, 17, 3, 2})};
  auto result = CalculateViewFromAbove(A);
  vector<LineSegment> golden_result = {
      LineSegment{0, 1, 0, 0},   LineSegment{1, 3, 1, 2},
      LineSegment{3, 4, 2, 1},   LineSegment{4, 5, 3, 3},
      LineSegment{5, 6, 2, 1},   LineSegment{6, 10, 0, 2},
      LineSegment{10, 11, 4, 0}, LineSegment{11, 13, 3, 2},
      LineSegment{13, 14, 4, 1}, LineSegment{14, 15, 2, 2},
      LineSegment{15, 16, 4, 0}, LineSegment{16, 17, 3, 2},
      LineSegment{17, 18, 4, 0}};
  assert(equal(result.begin(), result.end(), golden_result.begin(),
               golden_result.end(),
               [](const LineSegment& a, const LineSegment& b) {
                 return a.left == b.left && a.right == b.right &&
                        a.color == b.color && a.height == b.height;
               }));


  return 0;
}


