#include <algorithm>
#include <iostream>
#include <vector>

bool Compare(int num1, int num2) {
  return num1 > num2;
}

int main() {
  int n = 0;
  int k = 0;

  std::cin >> n >> k;

  std::vector<int> prices(n);

  for (int i = 0; i < n; i++) {
    std::cin >> prices[i];
  }

  std::sort(begin(prices), end(prices), Compare);

  int sum = 0;
  for (int i = 0; i < n; i++) {
    if (i % k != k - 1) {
      sum += prices[i];
    }
  }

  std::cout << sum << "\n";
}