/*
* IncrementArbitraryPrecisionInteger.cpp
* -----------------
*
* Chapter 6 Question 2
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> incrementInteger(vector<int> &num) {
        
    int sum = -1;

    for (int i = num.size() - 1; i > -1; i--) {
        sum = num[i] + 1 == 10 ? 0 : num[i] + 1;
        num[i] = sum;
        
        if (sum != 0) break; 
    }

    if (sum == 0)  num.insert(num.begin(), 1);

    return num;
}

vector <int> incrementIntegerClean(vector<int> &num) {
    num.back()++;

    for (int i = num.size() - 1; i > 0 && num[i] == 10; i--) {
        num[i] = 0; num[i-1]++;
    }

    if (num[0] == 10) {
        num[0] = 0;
        num.insert(num.begin(), 1);
    }

    return num;
}

int main()
{
    static const int arr[] = {9, 8, 5, 9, 9, 9, 6};
    static const int arr2[] = {9, 9, 9, 9};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> vec2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));  

    vec = incrementIntegerClean(vec2);

    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    
    

    // cout << endl;
    // for (int i = 0; i < vec.size(); i++) 
    //     cout << vec[i] << " ";

    //vector<int> vect1{ 10, 20, 30 }; 


    return 0;
}