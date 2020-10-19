/*
* BuySellStockKTimes.cpp
* -----------------
*
* Chapter 22 Question 3
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

double BuyAndSellStockOnce(vector<double>& prices) {
  double max_profit = 0, min_price_so_far = prices[0];

  for (int i = 1; i < prices.size(); i++) {
    max_profit = std::max(max_profit, (prices[i] - min_price_so_far));
    min_price_so_far = std::min(min_price_so_far, prices[i]);
  }
  
  return max_profit;
}

/**
 * 
 */
double BuyAndSellStockTwiceWithSpace(vector<double>& prices) {
  double max_profit = 0;  
  double min_so_far = prices[0], max_so_far = prices[prices.size() - 1];
  vector<double> max_buy_sell_once(prices.size(), 0);

  for (int i = 1; i < prices.size(); i++) {
    max_buy_sell_once[i] = std::max(max_buy_sell_once[i-1], prices[i] - min_so_far);
    min_so_far = std::min(min_so_far, prices[i]);
  }

  for (int i = prices.size() - 2; i >= 0; i--) {
    int profit = max_so_far - prices[i];
    max_profit = std::max(max_profit,  + max_buy_sell_once[i]);
    max_so_far = std::max(max_so_far, prices[i]);
  }

  return max_profit;
}

/**
 * Constant Space 
 */
double BuyAndSellStockTwice(vector<double>& prices) {
  std::pair<double, int> max_profit = {0, -1}; //profit to idx when purchased
  std::pair<double, int> second_largest_profit = {0, -1};
  double min_price_so_far_idx = 0;

  for (int i = 1; i < prices.size(); i++) {
    double profit = prices[i] - prices[min_price_so_far_idx];

    if (profit > max_profit.first) {
      if (max_profit.second != min_price_so_far_idx) {
        second_largest_profit = max_profit;
      }
      
      max_profit = {profit, min_price_so_far_idx};
    }

    else if (profit > second_largest_profit.first) {
      if (max_profit.second != min_price_so_far_idx) {
        second_largest_profit = {profit, min_price_so_far_idx};
      }
    } 
    
    if (prices[i] < prices[min_price_so_far_idx]) {
      min_price_so_far_idx = i;
    }
  }
  
  return max_profit.first + second_largest_profit.first;
}

double MaxProfitBuySellStockKTimes(const vector<double>& prices, int k) {
  vector<vector<int> > dp(k + 1, vector<int>(prices.size(), 0));

  int min_so_far_idx = 0;
  for (int i = 1; i < dp.size(); i++) {
    for (int j = 1; j < dp[0].size(); j++) {    
      int profit_if_sell_now = prices[j] - prices[min_so_far_idx];
      if (min_so_far_idx > 0) {
        profit_if_sell_now += dp[i-1][min_so_far_idx - 1];
      }
 
      dp[i][j] = std::max(dp[i][j-1], profit_if_sell_now);
      min_so_far_idx = prices[j] < prices[min_so_far_idx] ? j : min_so_far_idx;
    }
    min_so_far_idx = 0;
  }

  return dp[k][prices.size() - 1];
}

int main(int argc, char** argv) {   
  vector<double> prices{310, 315, 275, 295, 260, 270, 290, 230, 255, 250};
  vector<double> prices2{12, 11, 13, 9, 12, 8, 14, 13, 15};
  
  //min so far 
  // 0 0 0 0 0 0 0 0 0 
  // 0 0 2 2 3 3 6 6 7
  // 0 0 2 2 

  cout << BuyAndSellStockOnce(prices2) << endl;
  cout << BuyAndSellStockTwice(prices) << endl;
  cout << MaxProfitBuySellStockKTimes(prices, 2);

  return 0;
}


