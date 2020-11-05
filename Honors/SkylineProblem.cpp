/*
* SkylineProblem.cpp
* -----------------
*
* Chapter 22 Question 35
*/

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::greater;
using std::hash;
using std::istringstream;
using std::length_error;
using std::make_unique;
using std::map;
using std::unique_ptr;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::stoi;
using std::unordered_map;
using std::unordered_set;
using std::vector;

struct Rectangle {
  int left, right, height;
};

typedef vector<Rectangle> Skyline;

class Endpoint {
  public:
    bool operator<(const Endpoint& that) const {
      if (that.x != x) {
        return x < that.x;
      } else {
        if (that.isLeft && isLeft) {
          return height > that.height;
        } else if (!(that.isLeft || isLeft)) {
          return height < that.height;
        }
      }
      //cout << x << " " << that.x << " " << (x < that.x) << endl;
      return isLeft;
    }

    int x, height;
    bool isLeft;
};

Skyline ComputeSkyline(const vector<Rectangle>& buildings) {
  vector<Endpoint> endpoints;
  for (const auto& rect : buildings) {
    endpoints.emplace_back(Endpoint{rect.left, rect.height, true});
    endpoints.emplace_back(Endpoint{rect.right, rect.height, false});
  }
  sort(endpoints.begin(), endpoints.end());

  vector<Rectangle> results;
  map<int, int> queue;
  queue[0]++;
  
  Rectangle in_progress{endpoints[0].x, endpoints[0].x - 1, endpoints[0].height};
  for (int i = 1; i < endpoints.size(); i++) {
    int max_height = queue.crbegin()->first;
    Endpoint curr = endpoints[i];

    if (curr.isLeft) {
      if (curr.height > max_height) {
        in_progress.right = curr.x;
        results.emplace_back(in_progress);

        in_progress.left = curr.x, in_progress.height = curr.height;
      }

      queue[curr.height]++;
    } else {
      queue[curr.height]--;
      
      if (queue[curr.height] == 0) {
        queue.erase(curr.height);
      }

      if (max_height != queue.crbegin()->first){
        queue.erase(curr.height);

        //add completed rect to list
        in_progress.right = curr.x;
        results.emplace_back(in_progress);

        //start creating new rect 
        in_progress.left = curr.x, in_progress.height = queue.crbegin()->first;
      } 
    }
  }

  //complete last rectangle
  in_progress.right = endpoints[endpoints.size() - 1].x;
  results.emplace_back(in_progress);

  return results;
}

/**
* Book Solution
*/
void MergeIntersectSkylines(Skyline* merged, Rectangle* a, Rectangle* b, int* a_idx, int* b_idx) {
  if (a->right <= b->right) {
    if (a->height > b->height) {
      if (a->right != b->right) {
        merged->emplace_back(*a), (*a_idx)++;
        b->left = a->right;
      } else {
        ++*b_idx;
      }
    } else if (a->height == b->height) {
      b->left = a->left, ++*a_idx;
    } else {
      if (a->left != b->left) {
        merged->emplace_back(Rectangle{a->left, b->left, a->height}); 
      } 
      ++*a_idx;
    }
  } else { //a->right > b->right
    if (a->height >= b->height) {
      ++*b_idx;
    } else {
      if (a->left != b->left ) {
        merged->emplace_back(Rectangle{a->left, b->left, a->height});
      }
      a->left = b->right;
      merged->emplace_back(*b), ++*b_idx;
    }
  }
}

Skyline MergeSkylines(Skyline* left_skyline, Skyline* right_skyline) {
  int i = 0, j = 0;
  Skyline merged;
  
  while (i < (*left_skyline).size() && j < (*right_skyline).size()) {
    if ((*left_skyline)[i].right < (*right_skyline)[j].left) {
      merged.emplace_back((*left_skyline)[i++]);
    } else if ((*left_skyline)[i].left > (*right_skyline)[j].right) {
      merged.emplace_back((*right_skyline)[j++]);
    } else if ((*left_skyline)[i].left <= (*right_skyline)[j].left) {
      MergeIntersectSkylines(&merged, &(*left_skyline)[i], &(*right_skyline)[j], &i, &j);
    } else {
      MergeIntersectSkylines(&merged, &(*right_skyline)[j], &(*left_skyline)[i], &j, &i);
    }
  }

  merged.insert(merged.end(), left_skyline->begin() + i, left_skyline->end());
  merged.insert(merged.end(), right_skyline->begin() + j, right_skyline->end());

  return merged;
}

Skyline ComputeSkylineInInterval(const vector<Rectangle>& buildings, int left_endpoint, int right_endpoint) {
  
  if (right_endpoint - left_endpoint <= 1) {
    return {buildings.cbegin() + left_endpoint, 
            buildings.cbegin() + right_endpoint };
  } 
  
  int mid = left_endpoint + ((right_endpoint - left_endpoint) / 2);
  auto left_skyline = ComputeSkylineInInterval(buildings, left_endpoint, mid);
  auto right_skyline = ComputeSkylineInInterval(buildings, mid, right_endpoint);
  
  return MergeSkylines(&left_skyline, &right_skyline);
}

Skyline ComputeSkylineMergeSolution(const vector<Rectangle>& buildings) {
  return ComputeSkylineInInterval(buildings, 0, buildings.size());
}

int main(int argc, char** argv) {   
  vector<Rectangle> buildings;
  Rectangle a{0, 3, 1};
  Rectangle b{1, 6, 3};
  Rectangle c{4, 8, 4};
  Rectangle d{5, 9, 2};
  Rectangle e{11, 17, 1};
  Rectangle f{10, 12, 6};
  Rectangle g{7, 14, 3};
  Rectangle h{13, 16, 2};

  buildings.emplace_back(a);
  buildings.emplace_back(b);
  buildings.emplace_back(c);
  buildings.emplace_back(d);
  buildings.emplace_back(e);
  buildings.emplace_back(f);
  buildings.emplace_back(g);
  buildings.emplace_back(h);

  auto skyline = ComputeSkylineMergeSolution(buildings); 
  cout << skyline.size() << endl;
  for (auto rect : skyline) {
    cout << rect.left << " " << rect.right << " " << rect.height << endl;
  }            

  return 0;
}
