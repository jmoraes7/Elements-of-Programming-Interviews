/*
* TeamPhotoDay1.cpp
* -----------------
*
* Chapter 14 Question 9
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
using std::unordered_map;
using std::unordered_set;
using std::vector;

struct Person {
  bool operator <(const Person& that) const { return height < that.height; }
  
  int height;
};

class Team {
  public:
    explicit Team(const vector<int>& heights){
      for (int h : heights) {
        Person player{h};
        players_.push_back(player);
      } 
    }

    //checks if A can be place in front of B
    static bool valid_placement_exists(const Team& A, const Team& B) {
      vector<Person> A_sorted = A.sortPlayersByHeight();
      vector<Person> B_sorted = B.sortPlayersByHeight();

      // for (Person p : A_sorted) {
      //   cout << p.height << " ";
      // } 
      // cout << endl;

      // for (Person p : B_sorted) {
      //   cout << p.height << " ";
      // } 
      // cout << endl;
      // cout << endl;

      for (int i = A_sorted.size() - 1; i >= 0; --i) {
        if (!(A_sorted[i] < B_sorted[i])) {
          return false;
        }
      }
      return true;
    }

  private:
    vector<Person> sortPlayersByHeight() const {
      vector<Person> sorted_players(players_);
      sort(sorted_players.begin(), sorted_players.end());
      return sorted_players;
    }

    vector<Person> players_;
};

int main(int argc, char** argv) {
  vector<int> height{1, 5, 4};

  Team t1(height);
  height = {2, 3, 4};
  Team t2(height);
  assert(!Team::valid_placement_exists(t1, t2) && !Team::valid_placement_exists(t2, t1));

  height = {0, 3, 2};
  Team t3(height);
  assert(Team::valid_placement_exists(t3, t1) &&
         !Team::valid_placement_exists(t1, t3) &&
         Team::valid_placement_exists(t3, t2) &&
         !Team::valid_placement_exists(t1, t2));
  height = {1, 4, 2}; 
  Team t4(height);
  assert(!Team::valid_placement_exists(t4, t3));
  assert(!Team::valid_placement_exists(t3, t4));

  return 0;
}
