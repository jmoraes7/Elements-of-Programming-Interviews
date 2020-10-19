/*
* ComputeValidIPAddress.cpp
* -----------------
*
* Chapter 7 Question 10
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

using std::default_random_engine;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

bool isValidIP(string candidate) {
  
  if (candidate.size() > 3) return false;

  if (candidate.front() == '0' && candidate.size() > 1) { 
    return false;
  }
  
  int val = stoi(candidate);
  return val <= 255 && val >= 0;
}

vector<string> computeValidIPAddress(string base) {
  vector<string> addresses;
  int count = 0;
  for (int i = 1; i < 4 && i < base.size(); ++i) {
    auto first = base.substr(0, i); 
    
    for (int j = 1; j < 4 && i + j < base.size(); ++j) {
      auto second = base.substr(i, j);

      for (int k = 1; k < 4 && i + j + k < base.size(); ++k) {

        auto third = base.substr(i + j, k);
        auto fourth = base.substr(i + j + k);

        bool isValid = isValidIP(first) && isValidIP(second) && isValidIP(third) && isValidIP(fourth);

        if (isValid) {
          string address = first + '.' + second + '.' + third + '.' + fourth;
          addresses.push_back(address);
        }
        // cout << ++count << endl;
      }
    }
  }

  return addresses;
}

int main()
{  
  string base = "19216811";
  vector<string> ip_addresses = computeValidIPAddress(base);


  for (string word : ip_addresses) {
    cout << word << endl;
  }

  return 0;
}