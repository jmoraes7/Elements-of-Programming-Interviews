/*
* GeneratePrimes.cpp
* -----------------
*
* Chapter 6 Question 9
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double generatePrimes(vector<int> &prices) {
    int curr_profit_sell_today = 0;
    int larger_profit = 0;
    int smaller_profit = 0;
    
    int min_price_so_far = prices[0];

    for (int i = 1; i < prices.size(); ++i) {
        curr_profit_sell_today = max(prices[i] - min_price_so_far, curr_profit_sell_today);

        if (min_price_so_far > prices[i] || i == prices.size() - 1) {

            if (curr_profit_sell_today > larger_profit) {
                smaller_profit = larger_profit;
                larger_profit = curr_profit_sell_today;
            }

            else if (curr_profit_sell_today > smaller_profit) smaller_profit = curr_profit_sell_today;

            min_price_so_far = prices[i];
            curr_profit_sell_today = 0;
        }

        cout << larger_profit << " " << smaller_profit << endl;

    }

    return larger_profit + smaller_profit;
}

int main()
{ 
    static const int arr[] = {310, 315, 275, 295, 260, 270, 290, 230, 255, 250};

    static const int arr2[] = {12, 11, 13, 9, 12, 8, 14, 13, 15};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> vec2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));  
    
    double test = generatePrimes(vec);
    cout << test << endl;
   
    // for (int i = 0; i < vec.size(); i++) 
    //     cout << vec[i] << " ";
    
    return 0;
}