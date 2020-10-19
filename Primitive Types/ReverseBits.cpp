/*
* ReverseBits.cpp
* -----------------
*
* Chapter 5 Question 3
*/

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

vector<long> precomputedTable;

long swapBits(long x, int i, int j) {
  if (((x >> i) & 1) != ((x >> j) & 1)) {
    unsigned long bitMask = (1L << i) | (1L << j);
    x ^= bitMask;
  }
  return x;
}

long reverseBitsSlow(long x, int wordSize) {
  for (int i = 0; i < (wordSize / 2); i++) {
    x = swapBits(x, i, wordSize - i - 1);
  }
  return x;
}

void BuildReverseBitsTable() {
  for (int i = 0; i < (1 << 16); i++) {
    precomputedTable.push_back(reverseBitsSlow(i, 16));
  }
}

long ReverseBits(long x) {
  const int kWordSize = 16;
  const int kBitMask = 0xFFFF;

  return precomputedTable[x & kBitMask] << (3 * kWordSize) |
          precomputedTable[(x >> kWordSize) & kBitMask] << (2 * kWordSize) |
          precomputedTable[(x >> (2 * kWordSize)) & kBitMask] << kWordSize |
          precomputedTable[(x >> (3 * kWordSize)) & kBitMask];
}

int main(int argc, char** argv) {  
  BuildReverseBitsTable();
  
  default_random_engine gen((random_device())());
  for (int times = 0; times < 10; ++times) {
    uniform_int_distribution<long> dis(0, numeric_limits<long>::max());
    long x = dis(gen);
    cout << "x = " << x << ", reverse x = " << ReverseBits(x) << endl;
    assert(ReverseBits(x) == reverseBitsSlow(x, 64));
  }
  
  return 0;
}
