#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> Filter(
    std::vector<std::vector<int>>& weights, int v, int n
) {
  std::vector<std::vector<int>> in_graph;
  std::vector<std::vector<int>> out_graph;

  for (int i = 0; i < n; i++) {
    std::vector<int> in_indent;
    std::vector<int> out_indent;
    for (int j = 0; j < n; j++) {
      if (weights[i][j] <= v) {
        in_indent.push_back(j);
      }
      if (weights[j][i] <= v) {
        out_indent.push_back(j);
      }
    }
    in_graph.push_back(in_indent);
    out_graph.push_back(out_indent);
  }

  return {in_graph, out_graph};
}

bool BFS(std::vector<std::vector<int>>& graph, int n) {
  std::vector<int> visited(n);
  visited[0] = 1;
  std::deque<int> queue;
  queue.push_back(0);

  while (!queue.empty()) {
    int u = queue.front();
    queue.pop_front();

    for (int v : graph[u]) {
      if (visited[v] == 0) {
        visited[v] = 1;
        queue.push_back(v);
      }
    }
  }

  for (int v : visited) {
    if (v == 0) {
      return false;
    }
  }
  return true;
}

bool IsVPossible(std::vector<std::vector<int>>& weights, int v, int n) {
  auto [in, out] = Filter(weights, v, n);

  return BFS(in, n) && BFS(out, n);
}

int BinarySearch(std::vector<std::vector<int>>& weights, int min, int max, int n) {
  while (max - min > 1) {
    int mid = (max + min) / 2;
    if (IsVPossible(weights, mid, n)) {
      max = mid;
    } else {
      min = mid;
    }
  }
  if (IsVPossible(weights, max, n)) {
    return max;
  }
  return min;
}

int main() {
  int n;
  int min = 1000000000;
  int max = 0;
  std::cin >> n;

  std::vector<std::vector<int>> weights(n, std::vector<int>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> weights[i][j];
      min = std::min(min, weights[i][j]);
      max = std::max(max, weights[i][j]);
    }
  }

  std::cout << BinarySearch(weights, min, max, n) << "\n";
}