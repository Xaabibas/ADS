#include <iostream>
#include <vector>

bool IsDPossible(std::vector<int>& coord, int d, int k) {
  int cnt = 0;
  int previos = coord[0];
  k--;
  for (int c : coord) {
    cnt += c - previos;
    previos = c;
    if (cnt >= d) {
      k--;
      cnt = 0;
    }
  }

  return k <= 0;
}

int BinarySearch(std::vector<int>& coord, int k, int max, int min) {
  while (max - min > 1) {
    int mid = (max + min) / 2;
    if (IsDPossible(coord, mid, k)) {
      min = mid;
    } else {
      max = mid;
    }
  }
  if (IsDPossible(coord, max, k)) {
    return max;
  }
  return min;
}

int main() {
  int k, n;
  std::cin >> n >> k;
  std::vector<int> coord(n);

  for (int i = 0; i < n; i++) {
    std::cin >> coord[i];
  }
  int min = 1;
  int max = (coord[n - 1] - coord[0]) / (k - 1);
  int result = BinarySearch(coord, k, max, min);

  std::cout << result << "\n";
}