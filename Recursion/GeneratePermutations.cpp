/*
* GeneratePermutations.cpp
* -----------------
*
* Chapter 16 Question 3
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::stoi;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;
using std::stoul;
using std::swap;

/*
* Cracking The Coding Interview Solution #1
*/

string insertCharAt(string word, char c, int pos) {
  string prefix = word.substr(0, pos);
  string suffix = word.substr(pos);
  // cout << prefix << " " << c << " " << suffix << endl;
  return prefix + c + suffix;
}

vector<string> getPerms(string str) {

  vector<string> perms;

  if (str.size() == 0) {
    perms.push_back("");
    return perms;
  }

  char first = str[0];
  string remainder = str.substr(1);
  vector<string> words = getPerms(remainder);

  cout << "WORDS # " << words.size()  << endl;
  for (string word : words) {
    cout << word << endl;
    for (int i = 0; i <= word.size(); i++) {
      string s = insertCharAt(word, first, i);
      perms.push_back(s);
    }
  }

  return perms;
}

vector<vector<int> > generatePermutations2(vector<int> arr) {
  vector<vector<int> > result;

  std::string s;
  for (int x : arr) {
    s += std::to_string(x);
  }

  vector<string> perms = getPerms(s);

  int count = 20;
  cout << "FINAL WORDS" << endl;
  for (string s : perms) {
    vector<int> A;
    for (int i = 0; i < s.size(); ++i) {

      int x = (int) (s[i] - '0');
    
      A.push_back(x);
    }
    result.push_back(A);
  }

  return result;
}


/*
* Cracking The Coding Interview Solution #2
*/
vector<string> getPerms2(string s) {
  vector<string> perms;
  
  if (s.size() == 1) { perms.push_back(s); }
  
  else {

    for (int i = 0; i < s.size(); ++i) {
      
      char c = s[i];
      string pref = s.substr(0, i);
      string suff = s.substr(i+1); 

      vector<string> words = getPerms2(pref + suff);

      for (string word : words) {
        string perm = c + word;
        perms.push_back(perm);
      }
    }

  }

  return perms;
}


vector<vector<int> > generatePermutations3(vector<int> arr) {
  vector<vector<int> > result;

  std::string s;
  for (int x : arr) {
    s += std::to_string(x);
  }

  vector<string> perms = getPerms2(s);

  int count = 20;
  cout << "FINAL WORDS" << endl;
  for (string s : perms) {
    vector<int> A;
    for (int i = 0; i < s.size(); ++i) {

      int x = (int) (s[i] - '0');
    
      A.push_back(x);
    }
    result.push_back(A);
  }

  return result;
}

/*
* Book Solution #2
*/
vector<int> nextPermutation(vector<int>& perm) {
  int k = perm.size() - 2;
  while (k >= 0 && perm[k] >= perm[k+1]) {
    k--;
  }

  //perm is last permutation
  if (k == -1) { return vector<int>(); }

  for (int i = perm.size() - 1; i >= 0; --i) {
    if (perm[i] > perm[k]) {
      swap(perm[i], perm[k]);
      break;
    }
  }

  reverse(perm.begin() + k + 1, perm.end());

  return perm;
}

vector<vector<int> > generatePerm(vector<int> arr) {
  vector<vector<int> > results;

  sort(arr.begin(), arr.end());
  while (arr.size() != 0) {
    results.push_back(arr);
    arr = nextPermutation(arr);
  }

  return results;
}

/*
* Book Solution #1
*/

void permutationsHelper(int start, vector<int>* arr, vector<vector<int> >* results) {
  if (start == arr->size() - 1) {
    results->push_back(*arr);
    return;
  }

  for (int i = start; i < arr->size(); ++i) {
    // cout << i << " " << arr->size() << endl;
    swap((*arr)[i], (*arr)[start]);
    permutationsHelper(start + 1, arr, results);
    swap((*arr)[start], (*arr)[i]);
  }
}

vector<vector<int> > generatePermutations(vector<int> arr) {
  vector<vector<int> > permutations;
  permutationsHelper(0, &arr, &permutations);
  return permutations;
}  

void SmallTest() {
  
  vector<int> A{0, 1, 2};

  vector<vector<int> > result = generatePermutations3(A);

  vector<vector<int> > golden_result{{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
                                       {1, 2, 0}, {2, 1, 0}, {2, 0, 1}};

  
  for (int i = 0; i < result.size(); ++i) {
    for (int x : result[i]) {
      cout << x << " ";
    }
    cout << endl;
  }
 

  for (int i = 0; i < 6; ++i) {
    assert(equal(result[i].begin(), result[i].end(), golden_result[i].begin(),
                 golden_result[i].end()));
  }
}

int main(int argc, char **argv) {
  SmallTest();

  // default_random_engine gen((random_device())());
  // int n;
  // if (argc == 2) {
  //   n = stoul(argv[1]);
  // } else {
  //   uniform_int_distribution<int> dis(1, 10);
  //   n = dis(gen);
  // }
  // vector<int> A(n);
  // iota(A.begin(), A.end(), 0);
  // auto result = generatePermutations(A);
  // cout << "n = " << n << endl;
  // for (const auto &vec : result) {
  //   for (int a : vec) {
  //     cout << a << " ";
  //   }
  //   cout << endl;
  // }
  return 0;
}