#include <deque>
#include <iostream>
#include <queue>
const int IntMax = 2147483647;

struct Node {
  int ds{IntMax};
  bool visited{false};
  int x;
  int y;
  char type;
  Node* prev{nullptr};

  Node(int x, int y, char type) : x(x), y(y), type(type) {
  }
};

void Dijkstra(Node* start, std::vector<std::vector<Node>>& map, int n, int m) {
  std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, std::greater<>> pq;

  start->ds = 0;
  start->prev = start;
  pq.emplace(0, start);

  while (!pq.empty()) {
    auto [dist, v] = pq.top();
    pq.pop();

    if (v->visited) {
      continue;
    }
    v->visited = true;
    int x = v->x;
    int y = v->y;

    std::deque<Node*> neighbors;

    if (x != 0) {
      neighbors.push_back(&map[x - 1][y]);
    }
    if (y != 0) {
      neighbors.push_back(&map[x][y - 1]);
    }
    if (x != n - 1) {
      neighbors.push_back(&map[x + 1][y]);
    }
    if (y != m - 1) {
      neighbors.push_back(&map[x][y + 1]);
    }

    for (Node* neighbor : neighbors) {
      if (neighbor->type == '#' || neighbor->visited) {
        continue;
      }

      int w = (neighbor->type == '.' ? 1 : 2);

      if (v->ds + w < neighbor->ds) {
        neighbor->ds = v->ds + w;
        neighbor->prev = v;
        pq.emplace(neighbor->ds, neighbor);
      }
    }
  }
}

char Step(int dx, int dy) {
  if (dx == 1) {
    return 'S';
  }
  if (dx == -1) {
    return 'N';
  }
  if (dy == 1) {
    return 'E';
  }
  return 'W';
}

int main() {
  int n, m;
  std::cin >> n >> m;

  int x_start, y_start;
  std::cin >> x_start >> y_start;

  int x_end, y_end;
  std::cin >> x_end >> y_end;

  std::vector<std::vector<Node>> map;
  map.resize(n);

  for (int i = 0; i < n; i++) {
    map[i].reserve(m);
    for (int j = 0; j < m; j++) {
      char type;
      std::cin >> type;
      map[i].emplace_back(i, j, type);
    }
  }

  Node* start = &map[x_start - 1][y_start - 1];
  Dijkstra(start, map, n, m);

  Node* current = &map[x_end - 1][y_end - 1];

  if (current->ds == IntMax) {
    std::cout << -1 << "\n";
    return 0;
  }

  std::deque<char> root;

  while (current->prev != current) {
    Node* p = current->prev;

    if (!p) {
      std::cout << -1 << "\n";
      return 0;
    }

    int dx = current->x - p->x;
    int dy = current->y - p->y;

    root.push_front(Step(dx, dy));
    current = p;
  }

  std::cout << map[x_end - 1][y_end - 1].ds << "\n";
  for (char c : root) {
    std::cout << c;
  }
}