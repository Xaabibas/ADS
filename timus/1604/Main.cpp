#include <algorithm>
#include <iostream>
#include <vector>

struct Sign {
  int count;
  int index;
};

bool Compare(const Sign& sign1, const Sign& sign2) {
  return sign1.count > sign2.count;
}

int main() {
  int k = 0;
  int n = 0;
  std::cin >> k;

  std::vector<Sign> data(k);

  for (int i = 0; i < k; i++) {
    std::cin >> data[i].count;
    n += data[i].count;
    data[i].index = i + 1;
  }

  std::sort(begin(data), end(data), Compare);

  std::vector<int> signs(n);
  int sign_index = 0;

  int index = -(n % 2) + 1;
  while (index < n) {
    if (data[sign_index].count == 0) {
      sign_index++;
    }
    signs[index] = data[sign_index].index;
    data[sign_index].count--;
    index += 2;
  }

  index = 2 * (n % 2) / 2;
  while (index < n) {
    if (data[sign_index].count == 0) {
      sign_index++;
    }
    signs[index] = data[sign_index].index;
    data[sign_index].count--;
    index += 2;
  }

  for (int i = 0; i < n; i++) {
    std::cout << signs[i] << " ";
  }
}