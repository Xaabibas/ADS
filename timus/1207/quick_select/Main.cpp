#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

std::mt19937 Gen(std::random_device{}());

int GetRandom(int min, int max) {
  std::uniform_int_distribution<> dist(min, max);
  return dist(Gen);
}

struct Point {
  int index;
  int x;
  int y;
};

bool Compare(const Point& point1, const Point& point2) {
  if ((point1.x == 0 && point1.y == 0) || (point2.x == 0 && point2.y != 0)) {
    return true;
  }
  if ((point2.x == 0 && point2.y == 0) || (point1.x == 0 && point1.y != 0)) {
    return false;
  }

  int64_t mul1 = static_cast<int64_t>(point1.y) * point2.x;
  int64_t mul2 = static_cast<int64_t>(point2.y) * point1.x;

  return mul1 < mul2;
}

int Partition(std::vector<Point>& array, int left, int right, int pivot) {
  Point pivot_point = array[pivot];
  std::swap(array[pivot], array[right]);

  int store = left;
  for (int i = left; i < right; i++) {
    if (Compare(pivot_point, array[i])) {
      std::swap(array[store], array[i]);
      store++;
    }
  }

  std::swap(array[right], array[store]);
  return store;
}

Point QuickSelect(std::vector<Point>& array, int left, int right, int k) {
  if (left == right) {
    return array[left];
  }

  int pivot = GetRandom(left, right);
  pivot = Partition(array, left, right, pivot);

  if (k == pivot) {
    return array[k];
  }
  if (k < pivot) {
    return QuickSelect(array, left, pivot - 1, k);
  }
  return QuickSelect(array, pivot + 1, right, k);
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

  Point median = QuickSelect(array, 0, n - 1, n / 2 - 1);

  std::cout << start.index << " " << median.index << "\n";
}