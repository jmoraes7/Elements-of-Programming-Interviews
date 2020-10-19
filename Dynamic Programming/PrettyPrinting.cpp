/*
* PrettyPrinting.cpp
* -----------------
*
* Chapter 17 Question 13
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_real_distribution;
using std::string;
using std::vector;

int MinimizeMessinessInefficient(const vector<string>& words, int L) {
  vector<vector<int> > lc(words.size(), vector<int>(words.size(), -1));

  for (int i = 0; i < words.size(); i++) {
    int trailing_spaces = L - words[i].size();
    lc[i][i] = 1 << trailing_spaces;
    for (int j = i - 1 ; j >= 0; j--) {
      trailing_spaces -= (words[j].size() + 1);

      if (trailing_spaces < 0) {
        break;
      }
      lc[i][j] = 1 << trailing_spaces;
    }
  }

  vector<int> cost(words.size(), std::numeric_limits<int>::max());
  vector<int> line_indices(words.size());

  for (int i = 0; i < words.size(); i++) {
    for (int j = i; j >= 0; j--) {

      cout << "i: " << i << " j: " << j << " cost: " << lc[i][j] + cost[j-1] << " or " << cost[i] << endl;
      
      int candidate_cost = (j == 0 ? 0 : cost[j-1]) + lc[i][j];
      
      if (lc[i][j] != -1 && candidate_cost < cost[i]) {
        cost[i] = lc[i][j] + cost[j - 1];
        line_indices[i] = j;
      }
    }
  }

  for (int x : cost) {
    cout << x << " ";
  }
  cout << endl;

  for (int x : line_indices) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}

vector<vector<string> > MinimizeMessiness(const vector<string>& words, int L) {
  vector<long> M(words.size(), std::numeric_limits<long>::max());
  vector<int> line_indices(words.size());
  std::iota(line_indices.begin(), line_indices.end(), 0);

  for (int i = 0; i < words.size(); i++) {
    int trailing_spaces = L - words[i].size();
    M[i] = (i < 1 ? 0 : M[i - 1]) + (1 << trailing_spaces);

    for (int j = i - 1; j >= 0; j--) {
      trailing_spaces -= (words[j].size() + 1);
      if (trailing_spaces < 0) {
        break;
      }

      long candidate_Mi = (j - 1 < 0 ? 0 : M[j - 1]) + (1 << trailing_spaces);
      if (candidate_Mi < M[i]) {
        M[i] = candidate_Mi;
        line_indices[i] = j;
      }
    }
  }

  for (int x : M) {
    cout << x << " ";
  }
  cout << endl; 
  vector<vector<string> > pretty_text;
  int line_end_idx = line_indices.size() - 1;
  while (line_end_idx >= 0) {
    int line_start_idx = line_indices[line_end_idx];

    vector<string> line;
    for (int i = line_start_idx; i <= line_end_idx; i++) {
      line.push_back(words[i]);
    }
    pretty_text.insert(pretty_text.begin(), line);

    line_end_idx = line_start_idx - 1;
  }

  cout << "SCORE: " << M.back() << endl;
  return pretty_text;
}

int main(int argc, char** argv) {   
  vector<string> arr = {"aaa", "bb", "cc", "ddddd"};
  auto pretty_text = MinimizeMessiness(arr, 6);

  for (vector<string> line : pretty_text) {
    for (string word : line) {
      cout << word << " ";
    }
    cout << endl;
  }
  cout << endl;

  arr = {"aaa", "bbb", "c", "d", "ee", "ff", "gggggg"};
  pretty_text = MinimizeMessiness(arr, 11);

  for (vector<string> line : pretty_text) {
    for (string word : line) {
      cout << word << " ";
    }
    cout << endl;
  }
  cout << endl;
  
  arr = {"a", "b", "c", "d"};
  pretty_text = MinimizeMessiness(arr, 5);

  for (vector<string> line : pretty_text) {
    for (string word : line) {
      cout << word << " ";
    }
    cout << endl;
  }
  cout << endl;

  return 0;
}

