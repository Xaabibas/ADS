#include <cstdlib>
#include <iostream>
#include <queue>

struct Node {
  int value;
  int index;

  bool operator<(const Node& other) const {
    if (value == other.value) {
      return index > other.index;
    }
    return value > other.value;
  }
};

int main() {
  int n = 0;
  int k = 0;
  std::cin >> n >> k;

  std::priority_queue<Node> heap;

  for (int i = 0; i < k - 1; i++) {
    int value = 0;
    std::cin >> value;
    heap.push({value, i});
  }

  for (int i = k - 1; i < n; i++) {
    int value = 0;
    std::cin >> value;
    heap.push({value, i});

    Node top = heap.top();
    while (abs(top.index - i) > k - 1) {
      heap.pop();
      top = heap.top();
    }

    std::cout << top.value << " ";
  }
}