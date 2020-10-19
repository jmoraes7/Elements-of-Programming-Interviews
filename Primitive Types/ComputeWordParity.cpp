/*
* ComputeWordParity.cpp
* -----------------
*
* Chapter 5 Question 1
*/

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>

using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;

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

short Parity(unsigned long x) {
  int count = 0;
  while (x) {
    //cout << "COUNT: " << count << endl;
    count += (x & 1);
    x >>= 1;
  }
  //cout << "COUNT: " << count << endl; 
  return count % 2;
}

short Parity2(unsigned long x) {
  int count = 0;
  // cout << x << endl;
  // int_to_bin(x);

  while (x) {
    count ^= 1;
    x &= (x-1);
    //cout << x << endl;
    //int_to_bin(x);
  }

  return count;
}

array<short, (1 << 16)> BuildParityTable() {
  array<short, (1 << 16)> table;
  for (int i = 0; i < (1 << 16); ++i) {
    table[i] = Parity(i);
  }
  return table;
}

short Parity3(unsigned long x) {
  auto parityTable = BuildParityTable();

  const int kWordSize = 16;
  const int kBitMask = 0xFFFF; // 1111111111111111 in hex

  return parityTable[x >> (3 * kWordSize)] ^
          parityTable[(x >> (2 * kWordSize)) & kBitMask] ^
          parityTable[(x >> kWordSize) & kBitMask] ^
          parityTable[x & kBitMask]; 

}

short Parity4(unsigned long x) {
  x ^= x >> 32;
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return x & 0x1;
}

int main(int argc, char** argv) {  

  unsigned long x = 8;

  auto y = x & 1;

  cout << Parity(x) << endl << endl;

  cout << Parity2(x) << endl << endl;

  cout << Parity3(x) << endl << endl;

  cout << Parity4(x) << endl;

  return 0;
}
