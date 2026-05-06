#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::vector<std::vector<int>> Filter(std::vector<std::vector<int>>& weights, int v, int n) {
  std::vector<std::vector<int>> graph;

  for (int i = 0; i < n; i++) {
    std::vector<int> indent;
    for (int j = 0; j < n; j++) {
      if (weights[i][j] == 0) {
        continue;
      }
      if (weights[i][j] <= v) {
        indent.push_back(j);
      }
    }
    graph.push_back(indent);
  }

  return graph;
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
  std::vector<std::vector<int>> graph = Filter(weights, v, n);

  return BFS(graph, n);
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
  if (IsVPossible(weights, min, n)) {
    return min;
  }
  return max;
}

int main() {
  int n, m;
  int min = 1000000000;
  int max = 0;
  std::cin >> n >> m;

  std::vector<std::vector<int>> weights(n, std::vector<int>(n));

  for (int i = 0; i < m; i++) {
    int v1, v2, w;
    std::cin >> v1 >> v2 >> w;
    v1--;
    v2--;
    weights[v1][v2] = w;
    weights[v2][v1] = w;
    min = std::min(min, w);
    max = std::max(max, w);
  }

  int result = BinarySearch(weights, min, max, n);
  std::vector<std::vector<int>> result_graph = Filter(weights, result, n);
  std::vector<std::pair<int, int>> pairs;

  for (int v = 0; v < n; v++) {
    for (int u : result_graph[v]) {
      if (u > v) {
        pairs.emplace_back(v, u);
      }
    }
  }
  std::cout << result << "\n";
  std::cout << pairs.size() << "\n";
  for (auto [v1, v2] : pairs) {
    std::cout << ++v1 << " " << ++v2 << "\n";
  }
}