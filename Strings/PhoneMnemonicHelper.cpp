/*
* PhoneMnemonicHelper.cpp
* -----------------
*
* Chapter 7 Question 7
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

using std::default_random_engine;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;


void PhoneMnemonicHelper(string curr_mnemonic, string phone_number, vector<string> numToChar, vector<string>& mnemonics ) {

  if (phone_number == "") {
    mnemonics.push_back(curr_mnemonic);
  }

  int curr_digit = phone_number[0] - '0';
  string chars = numToChar[curr_digit - 2];
  
  for (const char& c : chars) {
    string new_mnemonic = curr_mnemonic + c;
    PhoneMnemonicHelper(new_mnemonic, phone_number.substr(1), numToChar, mnemonics);
  }
}

vector<string> PhoneMnemonic(const string& phone_number) {
  vector<string> mnemonics;
  vector<string> numToChar{"ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};
  
  PhoneMnemonicHelper("", phone_number, numToChar, mnemonics);

  return mnemonics;
}


int main()
{     
  vector<string> mnemonics = PhoneMnemonic("24");

  for (int i = 0; i < mnemonics.size(); ++i) {
      cout << mnemonics[i] << endl;
  }

  return 0;
}