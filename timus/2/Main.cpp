#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int current_sum = 0;
  int max_sum = 0;

  for (int i = 0; i < n; i++) {
    int p;
    std::cin >> p;

    if (current_sum + p > 0) {
      current_sum += p;
    } else {
      current_sum = 0;
    }

    if (current_sum > max_sum) {
      max_sum = current_sum;
    }
  }

  std::cout << max_sum << "\n";
}