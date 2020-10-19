/*
* ShortestProgramForX^n.cpp
* -----------------
*
* Chapter 19 Question 9
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::array;
using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::random_device;
using std::stoul;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

vector<int> ShortestProgramForXn(int n) {
  vector<int> start{1, 2};
  
  queue<vector<int> > q;
  q.emplace(start);

  while (!q.empty()) {
    vector<int> SLP = q.front();
    q.pop();

    for (const int& x : SLP) {
      int next_power = x + SLP.back();
      //cout << "NEXT: " << next_power << " BACK: " << SLP.back() << endl;
      if (next_power > n) {
        break;
      }

      vector<int> new_SLP(SLP);
      new_SLP.push_back(next_power);

      if (next_power == n) {
        return new_SLP;
      }

      for (int num : new_SLP) {
        cout << num << " ";
      }
      cout << endl;
      q.emplace(new_SLP);
    }
  }
  
  return {};
}

int main(int argc, char** argv) {   

  auto result = ShortestProgramForXn(8);
  cout << endl << "RESULT:" << endl;
  for (int x : result) {
    cout << x << " ";
  }

  return 0;
}


