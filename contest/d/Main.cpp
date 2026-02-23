#include <cstdint>
#include <iostream>

int main() {
  int64_t a, b, c, d, k;
  int64_t previous = -1;
  std::cin >> a >> b >> c >> d >> k;

  int current = a;

  for (int i = 0; i < k; i++) {
    current = current * b - c;
    if (current <= 0) {
      std::cout << 0;
      return 0;
    }
    if (current > d) {
      std::cout << d;
      return 0;
    }
    if (current == previous) {
      break;
    }
    previous = current;
  }
  std::cout << current;
}