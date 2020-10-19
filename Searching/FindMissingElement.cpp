/*
* FindMissingElement.cpp
* -----------------
*
* Chapter 12 Question 11
*/

#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

using std::bitset;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::ifstream;
using std::invalid_argument;
using std::ios;
using std::numeric_limits;
using std::ofstream;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

int FindMissingElement(ifstream* ifs) {
  const int kNumBucket = 1 << 16;
  vector<size_t> counter(kNumBucket, 0);
  unsigned int x;
  while (*ifs >> x) {
    int upper_part_x = x >> 16;
    counter[upper_part_x]++;
  }

  const int kBucketCapacity = 1 << 16;
  int candidate_bucket;
  for (int i = 0; i < kNumBucket; ++i) {
    if (counter[i] < kBucketCapacity) {
      candidate_bucket = i;
      break;
    }
  }

  ifs->clear();
  ifs->seekg(0, ios::beg);
  bitset<kBucketCapacity> bit_vec;
  while (*ifs >> x) {
    int upper_part_x = x >> 16;
    if (candidate_bucket == upper_part_x) {
      int lower_part_x = ((1 << 16) - 1) & x;
      bit_vec.set(lower_part_x); 
    }
  }
  ifs->close();

  for (int i = 0; i < kBucketCapacity; ++i) {
    if (bit_vec[i] == 0) {
      return (candidate_bucket << 16) | i;
    }
  }
}

int main(int argc, char** argv) {

  int n = 100;

  vector<int> A(1000000000);
  iota(A.begin(), A.end(), 0);
  unordered_set<int> hash;
  ofstream ofs("missing.txt");
  for (int i = 0; i < n; ++i) {
    hash.insert(A[i]);
    ofs << A[i] << endl;
  }
  A.clear();
  ofs.close();

  ifstream ifs("missing.txt");
  cout << "Before finding missing" << endl;
  int missing = FindMissingElement(&ifs);
  assert(hash.find(missing) == hash.cend());
  //Remove file after the execution.
  remove("missing.txt");
  cout << missing << endl;

  return 0;
}
