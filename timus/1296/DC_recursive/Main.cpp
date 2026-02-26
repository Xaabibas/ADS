#include <algorithm>
#include <iostream>
#include <vector>

struct Container {
  int sum;
  int pref;
  int suff;
  int best;
};

void Merge(const Container& left, const Container& right, Container& result) {
  result.sum = left.sum + right.sum;
  result.pref = std::max(left.pref, left.sum + right.pref);
  result.suff = std::max(right.suff, right.sum + left.suff);
  result.best = std::max(left.best, std::max(right.best, right.pref + left.suff));
}

void FindMax(std::vector<int>& array, int start, int end, Container& result) {
  if (end - start == 1) {
    int a = array[start];
    result.sum = a;
    result.pref = std::max(0, a);
    result.suff = std::max(0, a);
    result.best = std::max(0, a);
    return;
  }

  int mid = (start + end) / 2;
  Container left, right;
  FindMax(array, start, mid, left);
  FindMax(array, mid, end, right);

  Merge(left, right, result);
}

int main() {
  int n = 60000;
  std::cin >> n;

  if (n == 0) {
    std::cout << 0 << "\n";
    return 0;
  }

  std::vector<int> array(n);

  for (int i = 0; i < n; i++) {
    array[i] = 30000;
    std::cin >> array[i];
  }

  Container result;
  FindMax(array, 0, n, result);

  std::cout << result.best << '\n';
}