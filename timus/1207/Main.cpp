#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

struct Point {
  int index;
  int64_t x;
  int64_t y;
};

bool Compare(const Point& point1, const Point& point2) {
  if ((point1.x == 0 && point1.y == 0) || (point2.x == 0 && point2.y != 0)) {
    return true;
  }
  if ((point2.x == 0 && point2.y == 0) || (point1.x == 0 && point1.y != 0)) {
    return false;
  }

  return point1.y * point2.x < point2.y * point1.x;
}

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<Point> array(n);

  Point start{};
  start.index = 0;
  start.x = std::numeric_limits<int>::max();
  start.y = std::numeric_limits<int>::min();

  for (int i = 0; i < n; i++) {
    std::cin >> array[i].x;
    std::cin >> array[i].y;
    array[i].index = i + 1;

    if (array[i].x < start.x) {
      start = array[i];
    }
    if (array[i].x == start.x && array[i].y < start.y) {
      start = array[i];
    }
  }

  for (int i = 0; i < n; i++) {
    array[i].x -= start.x;
    array[i].y -= start.y;
  }

  std::sort(begin(array), end(array), Compare);

  std::cout << array[0].index << " " << array[n / 2].index << "\n";
}