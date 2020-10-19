/*
* FindMaxSimultaneousEvents.cpp
* -----------------
*
* Chapter 14 Question 5
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

struct Event {
  int start, end;
};

struct Endpoint {
  bool operator<(const Endpoint& e) const {
    return time != e.time ? time < e.time : (isStart && !isStart);
  }

  int time;
  bool isStart;
};

int FindMaxSimultaneousEventsClean(const vector<Event>& events) {
  int max_num_events = 0;
  int num_events = 0;

  vector<Endpoint> endpoints;

  for (Event event : events) {
    endpoints.push_back(Endpoint{event.start, true});
    endpoints.push_back(Endpoint{event.end, false});
  }

  sort(endpoints.begin(), endpoints.end());

  for (Endpoint endpoint : endpoints) {
    if (endpoint.isStart) {
      ++num_events;
      max_num_events = std::max(max_num_events, num_events);
    } else {
      --num_events;
    }
  }

  return max_num_events;
}

int FindMaxSimultaneousEvents(const vector<Event>& events) {
  int max_num_events = 0;
  int num_events = 0;

  vector<int> starts;
  vector<int> ends;

  for (Event e : events) {
    starts.push_back(e.start);
    ends.push_back(e.end);
  }

  std::sort(starts.begin(), starts.begin());
  std::sort(ends.begin(), ends.end());
  

  for (int x : ends) {
    cout << x << " ";
  }
  int i = 0, j = 0;
  while (i < starts.size()){
    cout << i << " " << j << " " << max_num_events << endl;
    if (starts[i] <= ends[j]) {
      ++i;
      ++num_events;
      max_num_events = std::max(max_num_events, num_events);
    } else {
      ++j;
      --num_events;
    }
  }
  
  return max_num_events;
}

int main(int argc, char** argv) {
  Event a{1, 5};
  Event b{2, 7};
  Event c{4, 5};
  Event d{6, 10};
  Event e{8, 9};
  Event f{9, 17};
  Event g{11, 13};
  Event h{12, 15};
  Event i{14, 15};

  vector<Event> events{a, b, c, d, e, f, g, h, i};

  vector<int> test;

  cout << FindMaxSimultaneousEventsClean(events) << endl;

  return 0;
}
