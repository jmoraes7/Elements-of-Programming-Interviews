/*
* RectangleIntersection.cpp
* -----------------
*
* Chapter 5 Question 11
*/

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

using std::array;
using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::invalid_argument;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;

struct Rectangle {
  int x, y, width, height;

  void print(string s) const {
    cout << s << this->x << ' ' << this->y << ' ' << this->width << ' '
         << this->height << endl;
  }
};

bool IsIntersecting(Rectangle R1, Rectangle R2) {
  return R1.x <= (R2.x + R2.width) && R1.y <= (R2.y + R2.height) &&
          R2.x <= (R1.x + R2.width) && R2.y <= (R1.y + R1.height);
}

Rectangle IntersectRectangle(Rectangle R1, Rectangle R2) {
  Rectangle result{0, 0, -1, -1};

  if (IsIntersecting(R1, R2)) {
    result = {std::max(R1.x, R2.x), std::max(R1.y, R2.y),
            std::min(R1.x + R1.width, R2.x + R2.width) - std::max(R1.x, R2.x),
            std::min(R1.y + R1.height, R2.y + R2.height) - std::max(R1.y, R2.y)};
  }

  return result; //no intersection
}

void SmallTest() {
  Rectangle R1 = {0, 0, 2, 2}, R2 = {1, 1, 3, 3};
  auto result = IntersectRectangle(R1, R2);
  assert(result.x == 1 && result.y == 1 && result.width == 1 &&
         result.height == 1);
  R1 = {0, 0, 1, 1}, R2 = {1, 1, 3, 3};
  result = IntersectRectangle(R1, R2);
  assert(result.x == 1 && result.y == 1 && result.width == 0 &&
         result.height == 0);
  R1 = {0, 0, 1, 1}, R2 = {2, 2, 3, 3};
  result = IntersectRectangle(R1, R2);
  assert(result.x == 0 && result.y == 0 && result.width == -1 &&
         result.height == -1);
}

int main(int argc, char** argv) {  
  SmallTest();  

  return 0;
}
 