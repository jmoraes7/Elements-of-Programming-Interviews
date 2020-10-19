/*
* FindStudentsWithHighestTestScores.cpp
* -----------------
*
* Chapter 13 Question 12
*/

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::greater;
using std::ifstream;
using std::istringstream;
using std::list;
using std::ofstream;
using std::priority_queue;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

int getScoreAverage(priority_queue<int, vector<int>, greater<int> > scores) {
  int sum = 0;
  int num_scores = scores.size();

  while (!scores.empty()) {
      cout << scores.top() << " ";
    sum += scores.top();
    scores.pop();
  }
  cout << endl;
  return sum / num_scores;
}

string FindStudentsWithHighestTestScores(ifstream* ifs) {
  unordered_map<string, priority_queue<int, vector<int>, greater<int> > > student_scores;
  
  string name;
  int score;
  while (*ifs >> name >> score) {
    student_scores[name].push(score);

    if (student_scores[name].size() > 3) {
      student_scores[name].pop();
    }
  }

  int max_score = 0;
  string top_student;
  for (const auto& scores : student_scores) {
    if (scores.second.size() == 3) {
      cout << scores.first << " ";
      int average = getScoreAverage(scores.second);

      cout <<  average << endl << endl;
      if (average > max_score) {
        max_score = average;
        top_student = scores.first;
      }
    }
  }

  return top_student;
}


void SimpleTest() {
  ofstream ofs("scores.txt");
  ofs << "adnan 100";
  ofs << "amit 99";
  ofs << "adnan 98";
  ofs << "thl 90";
  ofs << "adnan 10";
  ofs << "amit 100";
  ofs << "thl 99";
  ofs << "thl 95";
  ofs << "adnan 95";
  ofs.close();
  ifstream ifs("scores.txt");
  string result = FindStudentsWithHighestTestScores(&ifs);
  cout << "result = " << result << endl;
  assert(result == "adnan");
}

int main(int argc, char** argv) {    
  SimpleTest();
  
  return 0;
}
