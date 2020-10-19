/*
* SortStack.cpp
* -----------------
*
* Chapter 9 Question 8
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>
#include <random>

using namespace std;

using std::cout;
using std::default_random_engine;
using std::endl;
using std::istringstream;
using std::random_device;
using std::stack;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

struct BuildingWithHeight {
  int idx, height;
};

void insert(stack<int>& stack, int elem) {
  if (stack.empty() || elem >= stack.top()) {
    stack.push(elem);
  }

  else {
    int temp = stack.top();
    stack.pop();
    insert(stack, elem);
    stack.push(temp);
  }
}

void sort(stack<int>& stack) {
  if (!stack.empty()) {
    int elem = stack.top();
    stack.pop();
    sort(stack);
    insert(stack, elem);
  }
}

int main(int argc, char* argv[])
{  
  stack<int> stack;
  vector<int> elements{ 7, 3, 5, 10, -2 };

  for (int elem : elements) {
    stack.push(elem);
  }
  
  sort(stack);

  while (!stack.empty()) {
    cout << stack.top() << " ";
    stack.pop();
  }
  cout << endl;
  
  return 0;
}