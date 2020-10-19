/*
* ComputeFairBonus.cpp
* -----------------
*
* Chapter 22 Question 16
*/

#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::priority_queue;
using std::queue;
using std::shared_ptr;
using std::stoi;
using std::vector;

struct Compare {
  bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int> rhs) {
    return lhs.second > rhs.second;
  }
};

vector<int> ComputeFairBonusesInefficient(vector<int>& productivity) {

  vector<int> bonuses(productivity.size(), 1);
  priority_queue<std::pair<int, int>, vector<std::pair<int, int> >, Compare> min_heap;

  for (int i = 0; i < productivity.size(); i++) {
    min_heap.emplace(i, productivity[i]);
  }

  while (!min_heap.empty()) {
    int next_dev = min_heap.top().first;
    min_heap.pop();

    int candidate_bonus_from_left = bonuses[next_dev];
    if (next_dev > 0) {
      if (productivity[next_dev] > productivity[next_dev-1]) {
        candidate_bonus_from_left = bonuses[next_dev-1] + 1;
      } else if (productivity[next_dev] == productivity[next_dev-1]) {
        candidate_bonus_from_left = bonuses[next_dev-1];
      }
    } 

    int candidate_bonus_from_right = bonuses[next_dev];
    if (next_dev < bonuses.size() - 1) {
      if (productivity[next_dev] > productivity[next_dev+1]) {
        candidate_bonus_from_right = bonuses[next_dev+1] + 1;
      } else if (productivity[next_dev] == productivity[next_dev+1]) {
        candidate_bonus_from_right = bonuses[next_dev+1];
      }
    }
    
    bonuses[next_dev] = std::max(candidate_bonus_from_left, candidate_bonus_from_right);
  }

  return bonuses;
}


vector<int> ComputeFairBonuses(vector<int>& productivity) {
  vector<int> bonuses(productivity.size(), 1); //initially assigns bonus of 1 to everyone

  for (int i = 1; i < productivity.size(); i++) {
    if (productivity[i] > productivity[i-1]) {
      bonuses[i] = bonuses[i-1] + 1;
    }

    if (productivity[i] == productivity[i-1]) {
      bonuses[i] = bonuses[i-1];
    }
  }

  for (int i = productivity.size() - 2; i >= 0; i--) {
    if (productivity[i] > productivity[i+1]) {
      bonuses[i] = std::max(bonuses[i], bonuses[i+1] + 1);
    }

    if (productivity[i] == productivity[i+1]) {
      bonuses[i] = bonuses[i+1];
    }
  }

  return bonuses;
}

int main(int argc, char** argv) {   
  
  vector<int> A{1, 2, 4, 3, 1};

              // 1 2  3 3 0 2 2 1 
              //1  1  1  1  1  1  1

  auto results = ComputeFairBonuses(A);

  for (double x : results) {
    cout << x << " ";
  }
  cout << endl;

  results = ComputeFairBonusesInefficient(A);
  for (double x : results) {
    cout << x << " ";
  }
  
  return 0;
}


