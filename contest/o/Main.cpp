#include <deque>
#include <iostream>
#include <utility>
#include <vector>

bool BFS(
    int start,
    std::vector<int>& visited,
    std::vector<int>& colors,
    std::vector<std::vector<int>>& graph
) {
  visited[start] = 1;
  colors[start] = 0;
  std::deque<std::pair<int, int>> queue;
  queue.emplace_back(start, 0);

  while (!queue.empty()) {
    auto [u, l] = queue.front();
    queue.pop_front();

    for (int v : graph[u]) {
      if (visited[v] == 0) {
        visited[v] = 1;
        colors[v] = (l + 1) % 2;
        queue.emplace_back(v, l + 1);
      } else {
        if (colors[u] == colors[v]) {
          return true;
        }
      }
    }
  }

  return false;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n);
  std::vector<int> visited(n);
  std::vector<int> colors(n);

  for (int i = 0; i < m; i++) {
    int v1, v2;
    std::cin >> v1 >> v2;
    v1--;
    v2--;

    graph[v1].push_back(v2);
    graph[v2].push_back(v1);
  }

  int pointer = 0;
  while (pointer < n) {
    if (visited[pointer] == 1) {
      pointer++;
      continue;
    }
    if (BFS(pointer, visited, colors, graph)) {
      std::cout << "NO\n";
      break;
    }
  }
  if (pointer == n) {
    std::cout << "YES\n";
  }
}