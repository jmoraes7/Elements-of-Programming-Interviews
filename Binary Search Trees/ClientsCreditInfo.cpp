/*
* BinaryTreeNodesTotallyOrdered.cpp
* -----------------
*
* Chapter 15 Question 14
*/
#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::set;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class ClientsCreditsInfo {
  public:
    void Insert(const string& client_id, int credit) {
      Remove(client_id);

      int credits_adjusted = credit - offset_;
      clients_to_credits[client_id] = credits_adjusted;
      credits_to_clients[credits_adjusted].insert(client_id);
    }

    bool Remove(const string& client_id) {
      auto credit_iter = clients_to_credits.find(client_id);
      if (credit_iter != clients_to_credits.end()) {
        
        credits_to_clients[credit_iter->second].erase(client_id);

        if (credits_to_clients[credit_iter->second].empty()) {
          credits_to_clients.erase(credit_iter->second);
        }

        clients_to_credits.erase(client_id);
        return true;
      }

      return false;
    }

    int Lookup(const string& client_id) {
      auto client_iter = clients_to_credits.find(client_id);
      return client_iter == clients_to_credits.end() ? -1 : 
              clients_to_credits[client_id] + offset_;
    }

    void AddAll(int C) { offset_ += C; }

    string Max() const {
      auto iter = credits_to_clients.crbegin();
      return iter == credits_to_clients.crend() || iter->second.empty() ?
              "" : *(iter->second).begin();
    }

  
  private:
    int offset_ = 0;
    unordered_map<string, int> clients_to_credits;
    map<int, unordered_set<string> > credits_to_clients;


};

int main(int argc, char** argv) {   

  ClientsCreditsInfo a;
  assert(a.Max() == "");
  assert(!a.Remove("foo"));
  a.Insert("foo", 10);
  a.Insert("foo", 1);
  a.Insert("bar", 2);
  a.AddAll(5);
  a.Insert("widget", 3);
  a.AddAll(5);
  a.Insert("dothis", 4);
  assert(11 == a.Lookup("foo"));
  assert(12 == a.Lookup("bar"));
  assert(8 == a.Lookup("widget"));
  assert(4 == a.Lookup("dothis"));
  assert(a.Remove("foo"));
  assert(-1 == a.Lookup("foo"));

  assert(a.Max().compare("bar") == 0);
  a.Insert("xyz", 13);
  assert(a.Max().compare("xyz") == 0);
  a.Insert("dd", 15);
  assert(a.Max().compare("dd") == 0);
  
  return 0;
}

