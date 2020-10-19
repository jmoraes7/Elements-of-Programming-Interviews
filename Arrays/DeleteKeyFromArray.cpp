/*
* DeleteKeyFromArray.cpp
* -----------------
*
* Chapter 6 Question 5
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> deleteKeyFromArray(vector<int> &vec, int key) {

    int numKeysFound = 0;
    
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == key) {
            numKeysFound++;
            vec[i]++;
        } else {
            swap(vec[i], vec[i - numKeysFound]);
        }
    }

    return vec;
}

//DOESN'T WORK
//This is the book's solution
vector<int> deleteKeyFromArrayClean(vector<int> &vec, int key) {
    int index = 0;

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != key) {
            vec[index++] = vec[i];
        }
        
        if (vec[vec.size() - 1] == key) vec[vec.size()-1]++;
        cout << index << endl;
    }
    
    return vec;
}

int main()
{
    //  index = 4
    //  i = 6
    static const int arr[] = {5, 0, 7, 11, 2, 0, 13};

    static const int arr2[] = {2, 4, 1, 1, 0, 1, 0};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> vec2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));  

    
    vec = deleteKeyFromArray(vec, 0);

    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    return 0;
}