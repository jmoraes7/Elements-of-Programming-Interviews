/*
* NormalizePathnames.cpp
* -----------------
*
* Chapter 9 Question 4
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>

using namespace std;

using std::length_error;
using std::max;
using std::stack;

string normalize(const string& path) {
  vector<string> path_names;

  if (path.front() == '/') {
    path_names.push_back("/");
  }

  stringstream ss(path);
  string token;
  const char delimiter = '/';

  while (getline(ss, token, delimiter)) {
    //cout << token << endl;

    if (token == "..") {
      if (path_names.empty() || path_names.back() == "..") {
        path_names.push_back(token);
      } else {
        if (path_names.back() == "/") {
          invalid_argument("Path Error: absolute path can't start with '..'");
        }
        path_names.pop_back();
      }    
    } 
    else if (token != "." && token != "") {
      path_names.push_back(token);
    }
  }

  string normalized_path;
  if (!path_names.empty()) {

    normalized_path = path_names.front();
    for (int i = 1; i < path_names.size(); ++i) {
      if (i == 1 && normalized_path == "/") {
        normalized_path += path_names[i]; 
      } else {
        normalized_path += "/" + path_names[i];
      }
    }
  }

  return normalized_path;
}


int main()
{  
  string expression = "/usr/lib/..///./bin/gcc";
  expression = "scripts//./../scripts/awkscripts/././";

  cout << normalize(expression) << endl;

  return 0;
}