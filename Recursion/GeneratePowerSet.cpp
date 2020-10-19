/*
* GeneratePowerSet.cpp
* -----------------
*
* Chapter 16 Question 4
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
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

void genPowerSetHelper(string prefix, string candidate_suff, vector<string>& results) {
  if (candidate_suff.size() == 0) { results.push_back(prefix); } 

  else {
    
    genPowerSetHelper(prefix, candidate_suff.substr(1), results);

    genPowerSetHelper(prefix + candidate_suff[0], candidate_suff.substr(1), results);

  }

}

vector<vector<int> > GeneratePowerSet(vector<int> A) {
  string s;
  for (int i = 0; i < A.size(); ++i) {
    s += std::to_string(A[i]);
  }
  cout << "STRING: " << s << endl;

  vector<string> results;
  genPowerSetHelper("", s, results);

  cout << "POWER SET: " << endl;
  for (string result : results) {
    cout << result << endl;
  }
  cout << endl;

}

/*
* Book's Solution #1 
*/ 
void generatePowerSetHelper(vector<int>& input_set, vector<int> selected_so_far,
                            int to_be_selected, vector<vector<int> >& power_set) {
  if (to_be_selected == input_set.size()) {
    power_set.push_back(selected_so_far);
    return;
  }

  //select curr element
  selected_so_far.push_back(input_set[to_be_selected]);
  generatePowerSetHelper(input_set, selected_so_far, to_be_selected + 1, power_set);

  //don't select curr element
  selected_so_far.pop_back();
  generatePowerSetHelper(input_set, selected_so_far, to_be_selected + 1, power_set);
}

vector<vector<int> > generatePowerSet(vector<int> A) {
  vector<vector<int> > power_set;
  vector<int> selected_so_far;
  generatePowerSetHelper(A, selected_so_far, 0, power_set);

  cout << "POWER SET: " << endl;
  for (vector<int> set_ : power_set) {
    for (int x : set_) {
      cout << x << " ";
    }
    cout << endl;
  }
  
  return power_set;
}

/*
* Book Solution #2
*/ 
vector<vector<int> > generatePowerSet2(vector<int> A) {
  vector<vector<int> > power_set; 

  return power_set;
}

void SimpleTest() {
  vector<vector<int>> golden_result{{},  {0},    {1},    {0, 1},
                                       {2}, {0, 2}, {1, 2}, {0, 1, 2}};
  auto result = generatePowerSet({0, 1, 2});
  assert(equal(result.begin(), result.end(), golden_result.begin(),
               golden_result.end()));
}

int main(int argc, char* argv[]) {
  SimpleTest();
  vector<int> S;
  if (argc >= 2) {
    for (int i = 1; i < argc; ++i) {
      S.push_back(atoi(argv[i]));
    }
  } else {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(1, 10);
    S.resize(dis(gen));
    iota(S.begin(), S.end(), 0);
  }
  auto power_set = GeneratePowerSet(S);
  for (const vector<int>& one_set : power_set) {
    copy(one_set.begin(), one_set.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }
  return 0;
}
