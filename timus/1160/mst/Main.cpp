#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using Edge = std::pair<int, int>;

std::pair<std::vector<std::pair<int, int>>, int> Prim(
    std::vector<std::vector<std::pair<int, int>>>& graph
) {
  int start = 0;
  int max = -1;
  std::priority_queue<std::pair<int, Edge>, std::vector<std::pair<int, Edge>>, std::greater<>>
      queue;
  std::vector<int> visited(graph.size());
  std::vector<Edge> edges;

  for (auto [neighbor, w] : graph[start]) {
    queue.emplace(w, std::make_pair(start, neighbor));
  }

  while (edges.size() != graph.size() - 1) {
    auto [c, pair] = queue.top();
    auto [v, u] = pair;

    queue.pop();

    if (visited[v] == 1 && visited[u] == 1) {
      continue;
    }
    visited[v] = 1;
    visited[u] = 1;

    edges.emplace_back(v + 1, u + 1);

    max = std::max(max, c);

    for (auto [neighbor, w] : graph[u]) {
      if (visited[neighbor] == 1) {
        continue;
      }
      queue.emplace(w, std::make_pair(u, neighbor));
    }
  }

  return {edges, max};
}

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> graph(n);

  for (int i = 0; i < m; i++) {
    int v1, v2, w;
    std::cin >> v1 >> v2 >> w;
    v1--;
    v2--;

    graph[v1].emplace_back(v2, w);
    graph[v2].emplace_back(v1, w);
  }

  auto [edges, result] = Prim(graph);

  std::cout << result << "\n";
  std::cout << edges.size() << "\n";

  for (auto [u, v] : edges) {
    std::cout << u << " " << v << "\n";
  }
}