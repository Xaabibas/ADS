#include <deque>
#include <iostream>
#include <vector>

void BFS(int start, std::vector<int>& visited, std::vector<std::vector<int>>& graph) {
  visited[start] = 1;
  std::deque<int> queue;
  queue.push_back(start);

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
}

int main() {
  int n;
  std::cin >> n;

  std::vector<std::vector<int>> graph(n);
  std::vector<int> visited(n);

  for (int i = 0; i < n; i++) {
    int v;
    std::cin >> v;
    v--;

    graph[i].push_back(v);
    graph[v].push_back(i);
  }

  int pointer = 0;
  int counter = 0;

  while (pointer < n) {
    if (visited[pointer] == 1) {
      pointer++;
      continue;
    }
    BFS(pointer, visited, graph);
    counter++;
  }

  std::cout << counter << "\n";
}