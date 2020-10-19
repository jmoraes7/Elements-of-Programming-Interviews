/*
* BuyAndSellStockOnce.cpp
* -----------------
*
* Chapter 6 Question 7
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double BuyAndSellStockOnce(vector<int> &vec) {
    int max_profit = 0;
    int min_price_so_far = vec[0];

    for (int i = 1; i < vec.size(); i++) {
        int profit_sell_today = vec[i] - min_price_so_far; 
        
        max_profit = max(max_profit, profit_sell_today);
        min_price_so_far = min(min_price_so_far, vec[i]);        
    }

    return max_profit;
}

int main()
{ 
    static const int arr[] = {310, 315, 275, 295, 260, 270, 290, 230, 255, 250};

    static const int arr2[] = {2, 3, 5, 7, 11, 13, 0, 0, 0};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> vec2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));  
    
    double test = BuyAndSellStockOnce(vec);
    cout << test << endl;
   
    // for (int i = 0; i < vec.size(); i++) 
    //     cout << vec[i] << " ";
    
    return 0;
}