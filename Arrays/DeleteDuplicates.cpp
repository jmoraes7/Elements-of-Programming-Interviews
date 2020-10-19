/*
* DeleteDuplicates.cpp
* -----------------
*
* Chapter 6 Question 6
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> deleteDuplicates(vector<int> &vec, int key) {

    int write_idx = 1;
    int last_seen = vec[0];
    
    for (int i = 1; i < vec.size(); ++i) {
        if (vec[i] != last_seen) {
            last_seen = vec[i];
            vec[write_idx++] = vec[i];

            if (i != write_idx - 1) vec[i] = 0;
        } 
        else vec[i] = 0;
    }

    return vec;
}

int main()
{ 
    int write_idx = 2;
    static const int arr[] = {2, 3, 5, 5, 7, 11, 11, 11, 13};

    static const int arr2[] = {2, 3, 5, 7, 11, 13, 0, 0, 0};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> vec2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));  

    // vector<int> vec(10);
    // for(auto it = vec.begin(); it != vec.end(); it++)
    // {
    //     cin >> *it;
    // }
    
    vec = deleteDuplicates(vec, 0);

    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    return 0;
}