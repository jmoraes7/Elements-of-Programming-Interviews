/*
* BuildBSTFromSortedArray.cpp
* -----------------
*
* Chapter 15 Question 10
*/
#include <cassert>
#include <cmath> 
#include <iostream>
#include <limits>
#include <memory>
#include <map>
#include <set>
#include <vector>

#include "../Binary Trees/BinaryTreeNode.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::set;
using std::unique_ptr;

unique_ptr<BinaryTreeNode<int> > BuildBSTFromSortedArrayHelper(vector<int> arr, int start, int end) {
  if (start > end) {
    return nullptr;
  }

  int mid = start + ((end - start) / 2);

  return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
            arr[mid],
            BuildBSTFromSortedArrayHelper(arr, start, mid - 1),
            BuildBSTFromSortedArrayHelper(arr, mid + 1, end)
  });
          
}

unique_ptr<BinaryTreeNode<int> > BuildBSTFromSortedArray(vector<int> arr) {
  return BuildBSTFromSortedArrayHelper(arr, 0, arr.size() - 1);  
}

static void SimpleTest() {
  vector<int> A{1, 2, 3, 4, 5};

  unique_ptr<BinaryTreeNode<int>> result = BuildBSTFromSortedArray(A);

  cout << result->data << " " << result->left->data << " " << result->left->right->data << " " << result->right->data << " " << result->right->right->data;
  // assert(3 == result->data);
  // assert(2 == result->left->data);
  // assert(1 == result->left->left->data);
  // assert(4 == result->right->data);
}

int main(int argc, char** argv) {      
  SimpleTest();
  return 0;
}
