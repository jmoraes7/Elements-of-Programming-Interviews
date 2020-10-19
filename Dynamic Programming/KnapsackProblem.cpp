/*
* KnapsackProblem.cpp
* -----------------
*
* Chapter 17 Question 6
*/
#include <algorithm>
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::hash;
using std::numeric_limits;
using std::random_device;
using std::tuple;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

struct Item {
  int weight, value;
};

bool cmp(struct Item a, struct Item b) {
  double ratio_a = a.value / a.weight;
  double ratio_b = b.value / b.weight;
  return ratio_a > ratio_b;
}

double FractionalKnapsack(double w, vector<Item> items) {
  sort(items.begin(), items.end(), cmp);

  int val = 0;
  int curr_item = 0;
  for (int i = 0; i < items.size(); i++) {
    curr_item = i;

    if (w - items[i].weight < 0) { break; }

    val += items[i].value;
    w -= items[i].weight;
  }

  Item final_item = items[curr_item];

  double fractional_val = ((double) w) / ((double) final_item.weight) * final_item.value;


  return val + fractional_val;
}

int Knapsack(int w, vector<Item> items) {
  vector<int> vals(w + 1, 0);

  for (Item item : items) {
    for (int i = w; i >= item.weight; i--) {
      vals[i] = std::max(vals[i], vals[i - item.weight] + item.value);
    }
  }

  return vals[w];
}

int main(int argc, char** argv) {   
  
  vector<Item> items{{20, 65},  {8, 35},   {60, 245}, {55, 195},
                        {40, 65},  {70, 150}, {85, 275}, {25, 155},
                        {30, 120}, {65, 320}, {75, 75},  {10, 40},
                        {95, 200}, {50, 100}, {40, 220}, {10, 99}};

  //vector<Item> items{{5, 60}, {3, 50}, {4, 100}, {2, 30}};

  vector<Item> fractional_items{{10, 60}, {20, 100}, {30, 120}};

  cout << Knapsack(130, items) << endl;  
  assert(695 == Knapsack(130, items));

  cout << FractionalKnapsack(50, fractional_items) << endl;

  return 0;
}

