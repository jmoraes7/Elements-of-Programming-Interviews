/*
* GenerateSubsetSizedK.cpp
* -----------------
*
* Chapter 16 Question 5
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

void GenerateSubsetSizedKHelper(vector<int> input_set, int k, int to_be_selected,
                                vector<int> selected_so_far, vector<vector<int> >& subsets) {
  if (k == 0) {
    subsets.push_back(selected_so_far);
    return;
  }

  if (to_be_selected == input_set.size()) { return; }

  selected_so_far.push_back(input_set[to_be_selected]);
  GenerateSubsetSizedKHelper(input_set, k - 1, to_be_selected + 1, selected_so_far, subsets);

  selected_so_far.pop_back();
  GenerateSubsetSizedKHelper(input_set, k, to_be_selected + 1, selected_so_far, subsets);
}

/*
* Book Solution
*/
void DirectedCombinationsHelper(int n, int k, int offset, vector<int> partial_combination,
                            vector<vector<int> >& subsets) {
  if (partial_combination.size() == k) {
    subsets.push_back(partial_combination);
    return;
  }

  const int kNumRemaining = k - partial_combination.size();
  for (int i = offset; i <= n && kNumRemaining <= n - i + 1; ++i) {

    partial_combination.push_back(i);

    DirectedCombinationsHelper(n, k, i + 1, partial_combination, subsets);

    partial_combination.pop_back();

  }
}

vector<vector<int> > DirectedCombinations(int n, int k) {
  vector<vector<int> > subsets;
  vector<int> partial_combination;

  DirectedCombinationsHelper(n, k, 1, partial_combination, subsets);

  return subsets; 
}

vector<vector<int> > GenerateSubsetSizedK(vector<int> A, int k) {
  vector<vector<int> > subsets;
  vector<int> selected_so_far;

  //GenerateSubsetSizedKHelper(A, k, 0, selected_so_far, subsets);
  DirectedCombinationsHelper(A.size(), k, 1, selected_so_far, subsets);

  return subsets;
}

int main(int argc, char* argv[]) {
  vector<int> arr{1, 2, 3, 4, 5};

  auto subsets = GenerateSubsetSizedK(arr, 2);

  for (vector<int> subset : subsets) { 
    for (int x : subset) {
      cout << x << " ";
    }
    cout << endl;
  }

  return 0;
}
