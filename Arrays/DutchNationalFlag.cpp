/*
* DutchNationalFlag.cpp
* -----------------
*
* Chapter 6 Question 1
*/

#include <iostream>
#include <vector>

using namespace std;

/*
*   2 Pass Solution
*   Time: O(n), Space: O(1)
*/
void DutchNationalFlag(vector<int> &arr, int idx) {
   
   int count = 0;
   int pivot = arr[idx];

   cout << endl << "PIVOT " << pivot << endl;

    //First pass: group elements smaller than pivot
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[count++]);
        }
    }

    // Second pass: group elements equal to pivot
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == pivot) {
            swap(arr[i], arr[count++]);
        }
    }
}

/*
*   1 Pass Solution
*   Time: O(n), Space: O(1)
*/
void DutchNationalFlagOptimal(vector<int> &arr, int idx) {
    int pivot = arr[idx];
    int smaller = 0,  equal = 0, larger = arr.size() - 1;

    while (equal <= larger) {

        if (arr[equal] < pivot) {
            swap(arr[equal++], arr[smaller++]);
        }
        else if (arr[equal] == pivot) {
            equal++;
        }
        else {
            swap(arr[equal], arr[larger--]);
        }

    }
}
/*
*   Reorder array so that all elements equal to 'val' appear first
*/
void pushValToFront(vector<int> &vec, int val) {

    int swap_index = -1;

    for (int i = vec.size() - 1; i >= 0; i--) {
        
        if (vec[i] == val && swap_index == -1) {
            swap_index = i;
        }

        if  (vec[i] != val && swap_index != -1) {
            swap(vec[i], vec[swap_index]);
            swap_index--;
        }
    }
}

int main()
{
    static const int arr[] = {3, 9, 7 , 10, -4, 2, 6, 3, 3, 3, -4, 14, 1};

    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));  


    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    
    //DutchNationalFlag(vec, 0);
    //DutchNationalFlagOptimal(vec, 0);
    pushValToFront(vec, -4);

    cout << endl;
    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";

    //vector<int> vect1{ 10, 20, 30 }; 


    return 0;
}