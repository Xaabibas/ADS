#include <cstdint>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

struct Node {
  int index;
  int number;
  int next_time;

  bool operator<(const Node& other) const {
    return next_time < other.next_time;
  }
};

int main() {
  int n, k, p;
  std::cin >> n >> k >> p;

  int counter = 0;

  std::vector<Node> seq(p);
  std::vector<int> next_times(n, -1);
  std::vector<Node> actual(n);
  std::priority_queue<Node> buffer;
  std::set<int> cars;

  int current = 0;
  for (int i = 0; i < p; i++) {
    Node node = {};
    node.index = i;
    std::cin >> current;
    current--;
    node.number = current;
    node.next_time = p + 1;
    int prev = next_times[current];

    if (prev != -1) {
      seq[prev].next_time = i;
    }
    next_times[current] = i;

    seq[i] = node;
  }

  for (Node node : seq) {
    if (cars.contains(node.number)) {
      buffer.push(node);
      actual[node.number].next_time = node.next_time;
      k++;
      continue;
    }

    if (buffer.size() < static_cast<uint64_t>(k)) {
      buffer.push(node);
      actual[node.number] = node;
      cars.insert(node.number);
      counter++;
      continue;
    }

    Node prev = buffer.top();
    cars.erase(prev.number);
    buffer.pop();
    buffer.push(node);
    cars.insert(node.number);
    actual[node.number] = node;
    counter++;
  }

  std::cout << counter << "\n";
}