/*
* MultiplyArbitraryPrecisionInteger.cpp
* -----------------
*
* Chapter 6 Question 4
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test(vector<int> &num1) {
    cout << num1.size() << endl;
    cout << sizeof(num1)/sizeof(num1[0]) << endl;

    
}

bool canReachEnd(vector<int> &vec) {

    int max_reached = 0;
    vector<bool> counts(vec.size(), false);
    counts.front() = true;
    
    for (int i = 0; i < vec.size() - 1; i++) {

        if (counts[i] == true && vec[i] + i > max_reached) { 

            int starting_idx = max_reached + 1;
            for (int j = starting_idx; j <= i + vec[i]; j++) {
                counts[j] = true;
                max_reached = j;
            }
        } 
    }

    return counts.back() > 0;
}

bool canReachEndClean(vector<int> &vec) {

    int maxReached = 0;
    for (int i = 0; i < vec.size() && i <= maxReached; i++) {
        maxReached = max(maxReached, vec[i] + i);
        cout << maxReached << endl;

    }

    return maxReached >= vec.size() - 1;
}

int numStepsToReachEnd(vector<int> &vec) {

    int max_reached = 0;
    vector<int> counts(vec.size(), 0);
    counts.front() = 1;
    
    for (int i = 0; i < vec.size() - 1; i++) {
        cout << max_reached << " " << vec[i] + i << " " << vec[i] << " " << i << " " << counts[i] << endl;

         if (counts[i] != 0 && vec[i] + i > max_reached) { 
            cout << "YUP" << endl;

            int starting_idx = max_reached + 1;
            for (int j = starting_idx; j <= i + vec[i]; j++) {
                if (counts[j] > vec[i] + 1 || counts[j] == 0) {
                    counts[j] = counts[i] + 1;
                    max_reached = j;
                }
            }
        } 
    }

    cout << "COUNTS" << endl;
    for (int i = 0; i < counts.size(); i++) 
        cout << counts[i] << " ";
    cout << endl;

    // while (counts.back() == 0) {
    //     counts.pop_back();
    // }

    return counts.back();
}

int main()
{

    //   {0, 1, 1, 1, 2, 3, 3, 3}

    //   {t, t, t, t, t, t, t, t}   
    static const int arr[] = {6, 1, 1, 1, 1, 1, 1 };

    static const int arr2[] = {2, 4, 1, 1, 0, 1, 0};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  
    vector<int> vec2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));  

    bool result = numStepsToReachEnd(vec2);
    cout << "RESULT: " << endl << result << endl;

    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    return 0;
}