/*
* PartitionArrayWithRepeatedEntries.cpp
* -----------------
*
* Chapter 14 Question 8
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
  int age;
  string name;
};

void GroupByAge(vector<Person>& person_array) {

  unordered_map<int, int> age_to_count;
  for (Person p : person_array) {
    age_to_count[p.age]++;
  }
  
  unordered_map<int, int> age_to_offset;
  int offset = 0;
  for (const auto& p : age_to_count) {
    cout << p.first << " " << p.second << endl;

    age_to_offset[p.first] = offset;
    offset += p.second;
  }

  while (age_to_offset.size()) {
    cout << "HELLO" << endl;
    auto from = age_to_offset.begin();
    auto to = age_to_offset.find(person_array[from->second].age);
    
    std::swap(person_array[from->second], person_array[to->second]);

    --age_to_count[to->first];
    if (age_to_count[to->first] > 0) {
      ++age_to_offset[to->first];
    } else {
      age_to_offset.erase(to);
    }
  }
}

static void SimpleTest() {
  vector<Person> people{Person({20, "foo"}), Person({10, "bar"}),
                        Person({30, "widget"}), Person({20, "something"})};

  GroupByAge(people);
  if (people[0].age == 10) {
    assert(people[1].age == 20 && people[2].age == 20 && people[3].age == 20);
  } else {
    assert(people[1].age == 20 && people[2].age == 20 && people[3].age == 10);
  }

  for (Person p : people) {
    cout << p.name << " " << p.age << endl;
  }
}

int main(int argc, char** argv) {
  SimpleTest();

  return 0;
}
