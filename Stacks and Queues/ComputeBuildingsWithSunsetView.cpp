/*
* ComputeBuildingsWithSunsetView.cpp
* -----------------
*
* Chapter 9 Question 7
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>
#include <random>

using namespace std;

using std::cout;
using std::default_random_engine;
using std::endl;
using std::istringstream;
using std::random_device;
using std::stack;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

struct BuildingWithHeight {
  int idx, height;
};

vector<int> computeBuildingsWithSunsetView(vector<int> building_heights) {
  int building_idx = 0, building_height;

  //Stores (building_idx, building_height) pair 
  stack<BuildingWithHeight> candidates;
  cout << "HEIGHTS: " << endl;
  
  for (int i = building_heights.size() - 1; i > -1; --i) {
    cout << building_heights[i] << " ";
    while (!candidates.empty() && building_heights[i] >= candidates.top().height) {
      candidates.pop();
    }

    candidates.push(BuildingWithHeight{building_idx++, building_heights[i]});
  }
  
  vector<int> buildings_with_view;
  while (!candidates.empty()) {
    buildings_with_view.push_back(candidates.top().height);
    candidates.pop();
  }

  return buildings_with_view;
} 

int main(int argc, char* argv[])
{  
  vector<int> buildings{4, 1, 9, 5, 3, 3, 10};
  
  auto res = computeBuildingsWithSunsetView(buildings);
  
  cout << endl << "SOLUTIONS: " << endl;
  for (int x : res) {
    cout << x << " ";
  }
  cout << endl;
  
  return 0;
}