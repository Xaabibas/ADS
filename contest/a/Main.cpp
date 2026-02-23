#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  int start = 1;
  int end = 0;
  int cnt = 0;
  int previous = 0;

  int answer[] = {1, 1};

  for (int i = 1; i <= n; i++) {
    int current = 0;
    std::cin >> current;

    if (previous == current) {
      if (++cnt == 3) {
        if (answer[1] - answer[0] < end - start) {
          answer[0] = start;
          answer[1] = end;
        }
        end = i;
        start = i - 1;
        cnt = 2;
        continue;
      }
    } else {
      cnt = 1;
    }
    end++;
    previous = current;
  }
  if (answer[1] - answer[0] < end - start) {
    answer[0] = start;
    answer[1] = end;
  }
  std::cout << answer[0] << " " << answer[1] << "\n";
}
