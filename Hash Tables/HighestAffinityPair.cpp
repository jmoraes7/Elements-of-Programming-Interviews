/*
* HighestAffinityPair.cpp
* -----------------
*
* Chapter 13 Question 14
*/

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::greater;
using std::ifstream;
using std::istringstream;
using std::list;
using std::ofstream;
using std::priority_queue;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

std::pair<string, string> HighestAffinityPair(ifstream* ifs) {

  unordered_map<string, unordered_set<string> > page_to_users;

  string page;
  string user;
  while (*ifs >> page >> user) {
    page_to_users[page].insert(user);
  }

  int max_affinity = 0;
  std::pair<string, string> affinity_pair;
  for (auto page = page_to_users.begin(); page != page_to_users.end(); ++page) {
    unordered_set<string> page_users = page->second;

    auto succeeding_pages_it = page;
    succeeding_pages_it++;

    while (succeeding_pages_it != page_to_users.end()) {
      int affinity = 0;

      for (string user : page_users) {
        if (succeeding_pages_it->second.count(user)) {
          affinity++;
        }
      }

      if (affinity > max_affinity) {
        max_affinity = affinity;
        affinity_pair = { page->first, succeeding_pages_it->first };
      }

      succeeding_pages_it++;
    }

  }
  return affinity_pair;
}

void SimpleTest() {
  ofstream ofs("/tmp/logs.txt");
  ofs << "yahoo ap42" << endl;
  ofs << "google ap42" << endl;
  ofs << "twitter thl" << endl;
  ofs << "google aa314" << endl;
  ofs << "google aa314" << endl;
  ofs << "google thl" << endl;
  ofs << "twitter aa314" << endl;
  ofs << "twitter ap42" << endl;
  ofs << "yahoo aa314" << endl;

  ofs.close();
  ifstream ifs("/tmp/logs.txt");
  auto result = HighestAffinityPair(&ifs);
  cout << result.first << " " << result.second;
  // assert((result.first == "y" && result.second == "c") ||
  //        (result.first == "c" && result.second == "a"));
}

int main(int argc, char** argv) {    
  SimpleTest();
  
  return 0;
}
