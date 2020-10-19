/*
* BuyAndSellStockTwice.cpp
* -----------------
*
* Chapter 6 Question 8
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;


double BuyAndSellStockTwice(vector<int> &prices) {
    int min_price_so_far = prices[0];
    int curr_profit = 0;
    int larger_profit = 0;
    int smaller_profit = 0;

    for (int i = 1; i < prices.size(); i++) {
        curr_profit =  max(curr_profit, prices[i] - min_price_so_far);
        
        if (prices[i] < min_price_so_far || i == prices.size() - 1) {
            min_price_so_far = prices[i];

            smaller_profit = max( min(larger_profit, curr_profit), smaller_profit);    
            larger_profit = max(larger_profit, curr_profit);

            curr_profit = 0;
        }
    }

    return larger_profit + smaller_profit;
}

double BuyAndSellStockTwiceTest(vector<int> &prices) {
    vector <int> first_buy_sell_profits(prices.size(), 0);
    int max_profit = 0;
    int curr_min = prices[0];
    for (int i = 0; i < prices.size(); i++) {
        int profit = prices[i] - curr_min;
        first_buy_sell_profits[i] = max(first_buy_sell_profits[i-1], profit);
        curr_min = min(curr_min, prices[i]);
    }

    int curr_max = prices[prices.size() - 1];
    for (int i = prices.size() - 2; i >= 0; i--) {
        curr_max = max(curr_max, prices[i]);
        max_profit = max(max_profit, curr_max - prices[i] + first_buy_sell_profits[i-1]);
    }

    return max_profit;
}



 
int main()
{ 
    static const int arr[] = {310, 315, 275, 295, 260, 270, 290, 230, 255, 250};

    static const int arr2[] = {12, 11, 13, 9, 12, 8, 14, 13, 15};
                              //0,  0,  2, 2,  3,  3, 6,   6, 7, 
                              // 7, 2,  2,  0

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> vec2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));  
    
    double test = BuyAndSellStockTwiceTest(vec2);
    cout << "Solution: " << test << endl;

    // for (int i = 0; i < vec.size(); i++) 
    //     cout << vec[i] << " ";
    
    return 0;
}