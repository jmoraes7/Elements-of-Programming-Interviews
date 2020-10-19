/*
* JustifyText.cpp
* -----------------
*
* Chapter 22 Question 8
*/

#include <array>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::array;
using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::random_device;
using std::stoul;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

string DistributeRemainingSpacesInLine(string line, int num_remaining_spaces, int num_words) {
  //cout << "LINE: " << line << " " << num_words << endl;
  if (num_words == 1) {
    return line + string(num_remaining_spaces, '_');
  }

  int num_blanks = num_words - 1;
  int spaces_per_blank = num_remaining_spaces / num_blanks;
  int remainder = num_remaining_spaces % num_blanks;

  string justified_line = "";
  for (int i = 0; i < line.size(); i++) {
    if (line.at(i) == ' ') {
      int extra_space = remainder > 0 ? 1 : 0;
      justified_line += string((spaces_per_blank + extra_space), ' ');
      remainder--;
    }

    justified_line += line.at(i);
  }

  return justified_line;
}

vector<string> JustifyText(vector<string> words, size_t L) { 
  
  vector<string> results; 
  
  string curr_line = words[0];
  int num_words_in_line = 1;
  int num_remaining_spaces = L - words[0].size();
  for (int i = 1; i < words.size(); i++) {

    num_remaining_spaces -= (words[i].size() + 1);

    if (num_remaining_spaces < 0) {
      int spaces_to_distribute = num_remaining_spaces += (words[i].size() + 1);
      string justified_line = DistributeRemainingSpacesInLine(curr_line, spaces_to_distribute, num_words_in_line);
      results.push_back(justified_line);
      
      curr_line = words[i];
      num_words_in_line = 1;
      num_remaining_spaces = L - words[i].size();
    } else {
      curr_line += (" " + words[i]);
      num_words_in_line++;
    }
  }

  string last_line = DistributeRemainingSpacesInLine(curr_line, num_remaining_spaces, 1);
  results.push_back(last_line);

  return results;
}

int main(int argc, char** argv) {   
  
  vector<string> words{"The", "quick", "brown", "fox", "jumped", "over", "the", 
                    "lazy", "dogs."};

  

  vector<string> justified_text = JustifyText(words, 11);

  for (string row : justified_text) {
    cout << row << endl;
  }
  cout << endl;

  words = {"This", "is", "an", "example", "of", "text", "justification."};
  justified_text = JustifyText(words, 16);

  for (string row : justified_text) {
    cout << row << endl;
  }
  cout << endl;

  words = {"What","must","be","acknowledgment","shall","be"};
  justified_text = JustifyText(words, 16);
  
  for (string row : justified_text) {
    cout << row << endl;
  }
  cout << endl;

  words = {"Science","is","what","we","understand","well","enough","to","explain"};
  justified_text = JustifyText(words, 20);

  for (string row : justified_text) {
    cout << row << endl;
  }
  cout << endl;

  return 0;
}


