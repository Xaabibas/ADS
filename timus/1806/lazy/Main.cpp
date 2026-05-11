#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using Queue = std::
    priority_queue<std::pair<int, int64_t>, std::vector<std::pair<int, int64_t>>, std::greater<>>;

const int Len = 10;
std::vector<int64_t> CountDegrees() {
  std::vector<int64_t> degrees(Len + 1);
  degrees[0] = 1;
  for (int64_t i = 1; i <= Len; i++) {
    degrees[i] = degrees[i - 1] * Len;
  }
  return degrees;
}
const std::vector<int64_t> Degrees = CountDegrees();

struct NodeInf {
  bool visited{false};
  int ds{0};
  int64_t prev{0};
};

int CountWeight(int64_t a, int64_t b, std::vector<int>& weights) {
  for (int i = Len - 1; i > 0; i--) {
    if (a / Degrees[i] != b / Degrees[i]) {
      return weights[Len - i - 1];
    }
  }
  return weights[Len - 1];
}

void Dijkstra(
    std::unordered_map<int64_t, NodeInf>& nodes,
    std::unordered_map<int64_t, int>& indexes,
    std::vector<int>& weights,
    int64_t start
) {
  Queue pq;
  nodes[start].ds = 0;
  nodes[start].prev = start;

  pq.emplace(0, start);

  while (!pq.empty()) {
    auto [dist, v] = pq.top();
    pq.pop();

    if (nodes[v].visited) {
      continue;
    }
    nodes[v].visited = true;

    for (int64_t i = 0; i < Len; i++) {
      int64_t base = (v / Degrees[i + 1]) * Degrees[i + 1] + v % Degrees[i];

      for (int64_t j = 0; j < Len; j++) {
        int64_t neighbor = base + (Degrees[i] * j);
        if (neighbor == v || indexes.find(neighbor) == indexes.end()) {
          continue;
        }
        if (nodes.find(neighbor) != nodes.end() && nodes[neighbor].visited) {
          continue;
        }
        int w = CountWeight(v, neighbor, weights);
        if (nodes.find(neighbor) == nodes.end() || nodes[neighbor].ds > nodes[v].ds + w) {
          nodes[neighbor].ds = nodes[v].ds + w;
          nodes[neighbor].prev = v;
          pq.emplace(nodes[neighbor].ds, neighbor);
        }
      }
      for (int64_t i = 0; i < Len; i++) {
        int64_t v_i = (v % Degrees[i + 1]) / Degrees[i];
        int64_t v_without_i = v - v_i * Degrees[i];
        for (int64_t j = i + 1; j < Len; j++) {
          int64_t v_j = (v % Degrees[j + 1]) / Degrees[j];
          int64_t v_without_i_j = v_without_i - v_j * Degrees[j];
          int64_t neighbor = v_without_i_j + v_j * Degrees[i] + v_i * Degrees[j];
          if (neighbor == v || indexes.find(neighbor) == indexes.end()) {
            continue;
          }
          if (nodes.find(neighbor) != nodes.end() && nodes[neighbor].visited) {
            continue;
          }
          int w = CountWeight(v, neighbor, weights);
          if (nodes.find(neighbor) == nodes.end() || nodes[neighbor].ds > nodes[v].ds + w) {
            nodes[neighbor].ds = nodes[v].ds + w;
            nodes[neighbor].prev = v;
            pq.emplace(nodes[neighbor].ds, neighbor);
          }
        }
      }
    }
  }
}

int main() {
  int n;
  std::cin >> n;

  std::vector<int> weights(Len);
  for (int i = 0; i < Len; i++) {
    std::cin >> weights[i];
  }

  int64_t start, end;
  std::unordered_map<int64_t, int> indexes;
  int64_t a;
  std::cin >> a;
  start = a;
  indexes[a] = 1;
  for (int i = 1; i < n - 1; i++) {
    std::cin >> a;
    indexes[a] = i + 1;
  }
  std::cin >> a;
  end = a;
  indexes[a] = n;

  std::unordered_map<int64_t, NodeInf> nodes;

  Dijkstra(nodes, indexes, weights, start);

  if (nodes.find(end) == nodes.end()) {
    std::cout << "-1\n";
  } else {
    std::cout << nodes[end].ds << "\n";
    int64_t current = end;
    int64_t previous = nodes[current].prev;

    std::deque<int> deque;
    deque.push_front(indexes[current]);

    while (previous != current) {
      deque.push_front(indexes[previous]);
      current = previous;
      previous = nodes[previous].prev;
    }
    std::cout << deque.size() << "\n";
    for (int i : deque) {
      std::cout << i << " ";
    }
  }
}