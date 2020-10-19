/*
* TaskAssignment.cpp
* -----------------
*
* Chapter 18 Question 2
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

vector<std::pair<int, int> > assignTasks(vector<int> tasks) {
  sort(tasks.begin(), tasks.end());
  
  vector<std::pair<int, int> > result;
  for (int i = 0; i < tasks.size() / 2; i++) {
    result.push_back({tasks[i], tasks[tasks.size() - i - 1]});
  }

  return result;
}


int main(int argc, char** argv) {   
  
  vector<int> tasks = {5, 2, 1, 6, 4, 4};

  auto pairs = assignTasks(tasks);

  for (auto task_pair : pairs) {
    cout << task_pair.first << " " << task_pair.second << endl;
  }

  return 0;
}


