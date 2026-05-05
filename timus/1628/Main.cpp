#include <iostream>
#include <set>

struct Segment {
  int x;
  int y;

  int a;
  int b;

  [[nodiscard]] bool Include(const Segment& other) const {
    return x <= other.x && x + a >= other.x + other.a && y <= other.y && y + b >= other.y + other.b;
  }

  void Print() const {
    std::cout << x << " " << y << " - " << a << " x " << b << "\n";
  }

  [[nodiscard]] std::pair<Segment, Segment> Split(int x_b, int y_b) const {
    Segment s1;
    Segment s2;
    if (a == 1) {
      s1 = {x, y, a, y_b - y};
      s2 = {x, y_b + 1, a, b - y_b + y - 1};
    } else {
      s1 = {x, y, x_b - x, b};
      s2 = {x_b + 1, y, a - x_b + x - 1, b};
    }
    return {s1, s2};
  }
};

struct CompareByX {
  bool operator()(const Segment& s1, const Segment& s2) const {
    if (s1.x == s2.x) {
      return s1.y > s2.y;
    }
    return s1.x < s2.x;
  }
};

struct CompareByY {
  bool operator()(const Segment& s1, const Segment& s2) const {
    if (s1.y == s2.y) {
      return s1.x > s2.x;
    }
    return s1.y < s2.y;
  }
};

template <typename T, typename N>
void Insert(Segment seg, std::set<Segment, T>& set, std::set<Segment, N>& other) {
  if (seg.a > 0 && seg.b > 0) {
    auto it = other.lower_bound(seg);

    if (!it->Include(seg)) {
      set.insert(seg);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  int k = 0;

  std::cin >> n >> m >> k;

  std::set<Segment, CompareByX> columns;
  std::set<Segment, CompareByY> rows;

  for (int i = 1; i <= m; i++) {
    Segment seg = {i, 1, 1, n};
    columns.insert(seg);
  }

  for (int i = 1; i <= n; i++) {
    Segment seg = {1, i, m, 1};
    Insert(seg, rows, columns);
  }

  for (int i = 0; i < k; i++) {
    int x = 0;
    int y = 0;
    std::cin >> y >> x;
    Segment black = {x, y, 1, 1};

    auto ver = columns.lower_bound(black);

    if (!ver->Include(black)) {
      ver = columns.end();
    }
    auto gor = rows.lower_bound(black);
    if (!gor->Include(black)) {
      gor = rows.end();
    }

    if (gor != rows.end() && ver != columns.end()) {
      auto pair_gor = gor->Split(x, y);
      auto pair_ver = ver->Split(x, y);

      rows.erase(gor);
      columns.erase(ver);

      Insert(pair_ver.first, columns, rows);
      Insert(pair_ver.second, columns, rows);
      Insert(pair_gor.first, rows, columns);
      Insert(pair_gor.second, rows, columns);

      continue;
    }

    if (gor != rows.end()) {
      auto pair_gor = gor->Split(x, y);

      rows.erase(gor);

      Insert(pair_gor.first, rows, columns);
      Insert(pair_gor.second, rows, columns);
    }
    if (ver != columns.end()) {
      auto pair_ver = ver->Split(x, y);

      columns.erase(ver);

      Insert(pair_ver.first, columns, rows);
      Insert(pair_ver.second, columns, rows);
    }
  }
  std::cout << columns.size() + rows.size() << "\n";
}
