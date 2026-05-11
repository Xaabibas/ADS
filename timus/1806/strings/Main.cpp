#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using String = std::string;
using Graph = std::unordered_map<String, std::set<std::pair<String, int>, std::greater<>>>;
using Queue = std::
    priority_queue<std::pair<int, String>, std::vector<std::pair<int, String>>, std::greater<>>;

const int Len = 10;

struct NodeInf {
  bool visited{false};
  int ds{0};
  String prev;
};

int CountWeight(String a, String b, std::vector<int>& weights) {
  for (int i = 0; i < Len; i++) {
    if (a[i] != b[i]) {
      return weights[i];
    }
  }
  return weights[Len - 1];
}

Graph BuildGraph(std::unordered_map<String, int>& indexes, std::vector<int>& weights) {
  Graph map;

  for (auto [v, ind] : indexes) {
    std::set<std::pair<String, int>, std::greater<>> indent;
    for (int i = 0; i < Len; i++) {
      for (int j = 0; j < Len; j++) {
        String neighbor = v;
        neighbor[i] = j + '0';
        if (neighbor == v) {
          continue;
        }
        if (indexes.find(neighbor) != indexes.end()) {
          indent.emplace(neighbor, CountWeight(v, neighbor, weights));
        }
      }
    }

    for (int64_t i = 0; i < Len; i++) {
      for (int64_t j = i + 1; j < Len; j++) {
        String neighbor = v;
        neighbor[i] = v[j];
        neighbor[j] = v[i];

        if (neighbor == v) {
          continue;
        }
        if (indexes.find(neighbor) != indexes.end()) {
          indent.emplace(neighbor, CountWeight(v, neighbor, weights));
        }
      }
    }

    map[v] = indent;
  }

  return map;
}

void Dijkstra(std::unordered_map<String, NodeInf>& nodes, Graph& graph, String start) {
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

    for (auto [neighbor, w] : graph[v]) {
      if (nodes.find(neighbor) != nodes.end() && nodes[neighbor].visited) {
        continue;
      }
      if (nodes.find(neighbor) == nodes.end() || nodes[neighbor].ds > nodes[v].ds + w) {
        nodes[neighbor].ds = nodes[v].ds + w;
        nodes[neighbor].prev = v;
        pq.emplace(nodes[neighbor].ds, neighbor);
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

  String start, end;
  std::unordered_map<String, int> indexes;
  String a;
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

  Graph graph = BuildGraph(indexes, weights);

  std::unordered_map<String, NodeInf> nodes;

  Dijkstra(nodes, graph, start);

  if (nodes.find(end) == nodes.end()) {
    std::cout << "-1\n";
  } else {
    std::cout << nodes[end].ds << "\n";
    String current = end;
    String previous = nodes[current].prev;

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