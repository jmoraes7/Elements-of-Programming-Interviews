/*
* ComputeSalaryCap.cpp
* -----------------
*
* Chapter 14 Question 11
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::vector;

double computeSalaryCap(vector<double> salaries, double target) {
  sort(salaries.begin(), salaries.end());
  int total = 0;
  for (int i = 0; i < salaries.size(); i++) {
    total += salaries[i];
  }

  double salary_reduction_target = total - target;

  double salaries_to_be_capped = 0;
  for (int i = salaries.size() - 1; i >= 0; i--) {
    salaries_to_be_capped += salaries[i];

    double cap = (salaries_to_be_capped - salary_reduction_target) / (salaries.size() - i);

    if (cap >= salaries[i - 1]) {
      return cap;
    }
  }

  return -1;
}

int main(int argc, char** argv) {  
  vector<double> salaries{90, 30, 100, 40, 20};
  double target = 210.;

  cout << computeSalaryCap(salaries, target) << endl;

  return 0;
}
