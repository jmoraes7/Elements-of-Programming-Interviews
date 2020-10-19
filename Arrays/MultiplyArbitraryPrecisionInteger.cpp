/*
* MultiplyArbitraryPrecisionInteger.cpp
* -----------------
*
* Chapter 6 Question 3
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test(vector<int> &num1) {
    cout << num1.size() << endl;
    cout << sizeof(num1)/sizeof(num1[0]) << endl;

    
}

vector<int> multiplyIntegers(vector<int> &num1, vector<int> &num2) {
    bool is_negative = (num1.front() < 0 && num2.front() > 0) || 
                        (num1.front() > 0 && num2.front() < 0);

    num1.front() = abs(num1.front()); num2.front() = abs(num2.front());

    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    vector<int> result(num1.size() + num2.size(), 0);

    int carry = 0;
    for (int i = 0; i < num1.size(); i++) {
        for (int j = 0; j < num2.size(); j++) {
            int product = num1[i] * num2[j];

            result[i + j] += num1[i] * num2[j];
            result[i + j + 1] += result[i + j] / 10;
            result[i+j] = result[i+j] %10;
        } 
    }

    while(result.size() != -1 && result.back() == 0) {
        result.pop_back();
    }

    reverse(result.begin(), result.end());
    if (is_negative) result.front() *= -1;

    return result;
}

int main()
{
    static const int arr[] = {-1, 2, 3};
    static const int arr2[] = {-9, 8, 7};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> vec2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));  

    //test(vec2);
    vec = multiplyIntegers(vec, vec2);

    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    // cout << endl;
    // for (int i = 0; i < vec.size(); i++) 
    //     cout << vec[i] << " ";

    //vector<int> vect1{ 10, 20, 30 }; 

    return 0;
}