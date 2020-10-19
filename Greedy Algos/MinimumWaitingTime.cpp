/*
* MinimumWaitingTime.cpp
* -----------------
*
* Chapter 18 Question 3
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

int MinimumWaitingTime(vector<int> service_time) {

  sort(service_time.begin(), service_time.end());

  int waiting_time = 0;
  for (int i = 0; i < service_time.size() - 1; i++) {
    waiting_time += service_time[i] * (service_time.size() - (i + 1));
  }
  return waiting_time;
}


int main(int argc, char** argv) {   
  
  vector<int> service_time = {5, 1, 2, 3};

  cout << MinimumWaitingTime(service_time) << endl;

  return 0;
}


