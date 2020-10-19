/*
* ComputeGrayCode.cpp
* -----------------
*
* Chapter 16 Question 10
*/

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_set>
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
using std::unordered_set;
using std::vector;
 
void int_to_bin(int num)
{
  char str[9] = {0};
  int i;
  for (i=7; i>=0; i--)
  {
    str[i] = (num&1) ? '1' : '0';
    num >>= 1;
  }
  cout << str << endl;
}

vector<int> GrayCodeIterative(int num_bits) {
  vector<int> codes;
  codes.push_back(0);
  int gray_code_set_size = pow(2, num_bits) - 1;

  int curr_bit = 0;
  for (int i = 0; i < num_bits; i++) {
    int new_code = codes.back() | (1 << i);

    codes.push_back(new_code);
  }

  for (int i = 0; i < num_bits; i++) {
    int new_code = codes.back() ^ (1 << i);
    codes.push_back(new_code);
  }

  codes.pop_back();
  return codes;
}

bool DiffersByOneBitSlow(int front, int back) {
  int num_diff_bits = 0;
  while (front && back) {
    int XOR_val = (front & 1) ^ (back & 1);
    
    if (XOR_val == 1) { //if bits differ
      num_diff_bits++;
    }

    if (num_diff_bits == 2) { return false; }
  }

  return true;
}

bool DiffersByOneBit(int x, int y) {
  int bit_difference = x ^ y;
  return bit_difference && !(bit_difference & (bit_difference -1));
}

bool DirectedGrayCode(int num_bits, unordered_set<int>& history, vector<int>& result) {
  if (result.size() == (1 << num_bits)) {
    return DiffersByOneBit(result.front(), result.back());
  }

  for (int i = 0; i < num_bits; i++) {
    int previous_code = result.back();
    int candidate_next_code = previous_code ^ (1 << i);

    if (!history.count(candidate_next_code)) {
      history.insert(candidate_next_code);
      result.push_back(candidate_next_code);
      
      if (DirectedGrayCode(num_bits, history, result)) {
        return true;
      }  

      history.erase(candidate_next_code);
      result.pop_back();
    }
  }

  return false;
}

vector<int> GrayCode(int num_bit) {
  vector<int> result;
  result.push_back(0);
  unordered_set<int> history;
  history.insert(0);
  DirectedGrayCode(num_bit, history, result);

  return result;
}

vector<int> GrayCodeBottomUp(int num_bits) {
  if (num_bits == 1) {
    return {0, 1};
  }

  vector<int> codes = GrayCodeBottomUp(num_bits - 1);
  for (int i = codes.size() - 1; i >= 0; i--) {
    int new_code = codes[i] | (1 << (num_bits - 1));
    codes.push_back(new_code);
  }

  return codes;
}

void SmallTest() {
  auto vec = GrayCode(3);
  vector<int> expected = {0, 1, 3, 2, 6, 7, 5, 4};
  assert(equal(vec.begin(), vec.end(), expected.begin(), expected.end()));
}

int main(int argc, char* argv[]) {
  
  vector<int> vec = GrayCode(3);

  for (int elem : vec) {
    int_to_bin(elem);
  }

  cout << endl << endl;

  auto res = GrayCodeBottomUp(3);
  for (int x : res) {
    cout << x << " ";
  }
  cout << endl;

  return 0;
}