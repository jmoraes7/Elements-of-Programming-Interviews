/*
* hello_world.cpp
* -----------------
*
* This program prints out Hello World on the command line
*/

#include <iostream>
#include <fstream>
#include <vector>
// #include <stack>
#include <map>

using namespace std;

template <typename Type>
void Swap(Type &a, Type &b) {
    Type tmp = a; 
    a = b;
    b = tmp;
}

void reverseResponse() {
    string response = "reverse this";

    stack<char> stack;

    for (int i = 0; i < response.length(); i++)
        stack.push(response[i]);
    
    cout << "The response backward is ";
    while (!stack.empty()) {
        cout << stack.top();
        stack.pop();
    }
}

vector<int> MakeRandomVector(int sz, int minRange, int maxRange) {

    srand(time(0));     
    std::vector<int> numbers;
    
    int range = maxRange - minRange;

    for (int i = 0; i < sz; i++)
        numbers.push_back(rand() % range + minRange);
    
    return numbers;
}

// void printVector(vector<int> &v) {

//     for (int i = 0; i < v.size(); i++) {
//         cout << v[i] << " ";
//     }
//     // for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i)
//     //     std::cout << *i << ' ';
// }

int C(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
    return C(n-1, k) + C(n-1, k-1);
}

void permute(string soFar, string rest) {

    if (rest == "") {
        cout << soFar << endl;
    } else {

        for (int i = 0; i < rest.length(); i++) {
            string next = soFar + rest[i];
            string remaining = rest.substr(0, i) + rest.substr(i+1);

            permute(next, remaining);
        }
    }
}

void recurseSubsets(string soFar, string rest) {
    if (rest == "") {
        cout << soFar << endl;

    } else { 
        recurseSubsets(soFar + rest[0], rest.substr(1));

        recurseSubsets(soFar, rest.substr(1));
    }
}
void generateSubsets(string s) {
    recurseSubsets("", s);
}

void listPermutations(string s) {
    permute("", s);
}

vector<int> selectionSort(vector<int> &nums) {

    for (int i = 0; i < nums.size(); i++) {
        int minIndex = i;
        for (int j = i; j < nums.size(); j++) {
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }

        int minElem = nums[minIndex];
        nums.erase(nums.begin() + minIndex);

        //swap min element with element at position i
        nums.insert(nums.begin() + i, minElem);
    }

    return nums;
}

template <typename Type>
vector<Type> insertionSort(vector<Type> &nums, int (cmp)(Type, Type)) {

    for (int i = 0; i < nums.size(); i++) {
        int insertionIndex;
        int cur = nums[i];

        for (int j = i-1; j >= 0 && nums[j] > cur; j--) {
            
            //std::iter_swap(nums.begin() + j , nums.begin() + j+1);
            swap(nums[j], nums[j+1]);            
        }
    }

    return nums;
} 

void merge(vector<int>left, vector<int> right, vector<int>& arr)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR) 
    {
        if (left[j] <= right[k]) {
            arr[i] = left[j];
            j++;
        }
        else {
            arr[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        arr[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        arr[i] = right[k];
        k++; i++;
    }
}

void mergeSort(vector<int> & bar) {
    if (bar.size() <= 1) return;

    int mid = bar.size() / 2;

    vector<int> left;
    vector<int> right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    mergeSort(left);
    mergeSort(right);
    merge(left, right, bar);
}

int partition(vector<int> &nums, int left, int right) {
    int pivotIndex = left + (right - left) / 2; //same as (l + r) / 2 but minimizes chance of overflow if left/right are big
    int pivotVal = nums[pivotIndex];

    while (left <= right) {

        while (nums[left] < pivotVal) left++;
        while (nums[right] > pivotVal) right--;

        if (left <= right) {
            swap(nums[right], nums[left]);
            left++;
            right--;
        }
    }
    
    return left;
}

void quicksort(vector<int> &nums, int left, int right) 
{
    if (left < right) {
        int pivot = partition(nums, left, right);
        quicksort(nums, left, pivot - 1);
        quicksort(nums, pivot, right);
    }
}

int comparator(int a, int b) {
    if (a < b) return 1;
    if (b > a) return -1;
    return 0;
}

int main() 
{

    //cout << C(15, 11) << endl;

    //listPermutations("ABCD");
    //cout << "SUBSETS: " << endl;

    //generateSubsets("ABCD");
    std::vector<int> nums = MakeRandomVector(25, 0, 100);

    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";

    //nums = insertionSort(nums, comparator);

    quicksort(nums, 0, nums.size()-1);

    cout << endl << "SORTED LIST: " << endl;
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    cout << endl;

    return 0;
}