/*
* TowersOfHanoi.cpp
* -----------------
*
* Chapter 16 Question 1
*/

#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <stack>

using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stack;
using std::uniform_int_distribution;

const int kNumPegs = 3; 

static int num_steps;

void ComputeTowerOfHanoiSteps(int num_rings_to_move, array<stack<int>, kNumPegs>& pegs,
                              int from_peg, int to_peg, int use_peg) {

  if (num_rings_to_move > 0) {

    ComputeTowerOfHanoiSteps(num_rings_to_move - 1, pegs, from_peg, use_peg, to_peg);

    pegs[to_peg].push(pegs[from_peg].top());
    pegs[from_peg].pop();
    num_steps++;

    //cout << "Moved ring from peg " << from_peg << " to peg " << to_peg << endl; 
    
    ComputeTowerOfHanoiSteps(num_rings_to_move - 1, pegs, use_peg, to_peg, from_peg);

  }
}

void ComputeTowerHanoi(int num_rings) {
  array<stack<int>, kNumPegs> pegs;
  for (int i = num_rings; i > 0; --i) {
    pegs[0].push(i);
  }

  ComputeTowerOfHanoiSteps(num_rings, pegs, 0, 1, 2);
}

int main() {
  int n;

  num_steps = 0;
  ComputeTowerHanoi(4);
  assert(15 == num_steps);

  num_steps = 0;
  ComputeTowerHanoi(1);
  assert(1 == num_steps);

  num_steps = 0;
  ComputeTowerHanoi(0);
  assert(0 == num_steps);

  num_steps = 0;
  ComputeTowerHanoi(10);
  assert(1023 == num_steps);
  return 0;
}