/*
* AnonymousLetter.cpp
* -----------------
*
* Chapter 13 Question 3
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

string RandString(int len) {
  string ret;
  default_random_engine gen((random_device())());
  while (len--) {
    uniform_int_distribution<int> dis(0, 26);
    int x = dis(gen);
    ret += (x < 26) ? 'a' + x : ' ';
  }
  return ret;
}

bool IsLetterConstructibleFromMagazine(string letter, string magazine) {
  if (letter == "") { return true; }

  unordered_map<char, int> letter_char_freq;
  for (int i = 0; i < letter.size(); i++) {
    letter_char_freq[letter[i]]++;
  }

  for (const auto& c : magazine) {   
    if (letter_char_freq.find(c) != letter_char_freq.end()) {
      letter_char_freq[c]--;
      if (letter_char_freq[c] == 0) {
        letter_char_freq.erase(c);

        if (letter_char_freq.empty()) {
          return true;
        }
      }
    } 
  }

  return letter_char_freq.empty();
}

void SimpleTest() {
  assert(!IsLetterConstructibleFromMagazine("123", "456"));
  assert(!IsLetterConstructibleFromMagazine("123", "12222222"));
  assert(IsLetterConstructibleFromMagazine("123", "1123"));
  assert(IsLetterConstructibleFromMagazine("123", "123"));
  assert(!IsLetterConstructibleFromMagazine("12323", "123"));
  assert(
    IsLetterConstructibleFromMagazine("GATTACA", "A AD FS GA T ACA TTT"));
  assert(!IsLetterConstructibleFromMagazine("a", ""));
  assert(IsLetterConstructibleFromMagazine("aa", "aa"));
  assert(IsLetterConstructibleFromMagazine("aa", "aaa"));
  assert(IsLetterConstructibleFromMagazine("", "123"));
  assert(IsLetterConstructibleFromMagazine("", ""));

}

int main(int argc, char** argv) {  
  SimpleTest();  

  return 0;
}
