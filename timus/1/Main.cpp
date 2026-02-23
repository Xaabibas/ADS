#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
  int value;
  char name;
  std::vector<Node*> neighbors;
};

Node MakeNode(int value, char name) {
  Node node;
  node.value = value;
  node.name = name;
  return node;
}

void ClearPair(Node* a, Node* b) {
  int min = std::min(a->value, b->value);
  if (min > 0) {
    a->value -= min;
    b->value -= min;
    for (int i = 0; i < min; i++) {
      std::cout << a->name << b->name << "-\n";
    }
  }
}

void TruncateNode(Node* node) {
  if (node->value == 0) {
    return;
  }
  for (Node* neighbor : node->neighbors) {
    ClearPair(node, neighbor);
  }
}

void Fix(Node* node) {
  int times = node->value;
  switch (node->name) {
    case 'A':
    case 'G':
      for (int i = 0; i < times; i++) {
        std::cout << "EF+\n";
        std::cout << "AE-\n";
        std::cout << "FG-\n";
      }
      break;
    case 'B':
    case 'H':
      for (int i = 0; i < times; i++) {
        std::cout << "EF+\n";
        std::cout << "HE-\n";
        std::cout << "FB-\n";
      }
      break;
    case 'C':
    case 'E':
      for (int i = 0; i < times; i++) {
        std::cout << "HG+\n";
        std::cout << "HE-\n";
        std::cout << "GC-\n";
      }
      break;
    case 'D':
    case 'F':
      for (int i = 0; i < times; i++) {
        std::cout << "HG+\n";
        std::cout << "HD-\n";
        std::cout << "GF-\n";
      }
      break;
  }
}

int main() {
  int a, b, c, d, e, f, g, h;
  std::cin >> a >> b >> c >> d >> e >> f >> g >> h;

  int sum1 = a + c + f + h;
  int sum2 = b + d + e + g;

  if (sum1 != sum2) {
    std::cout << "IMPOSSIBLE\n";
    return 0;
  }

  Node A = MakeNode(a, 'A');
  Node B = MakeNode(b, 'B');
  Node C = MakeNode(c, 'C');
  Node D = MakeNode(d, 'D');
  Node E = MakeNode(e, 'E');
  Node F = MakeNode(f, 'F');
  Node G = MakeNode(g, 'G');
  Node H = MakeNode(h, 'H');
  A.neighbors = {&B, &D, &E};
  B.neighbors = {&A, &C, &F};
  C.neighbors = {&B, &D, &G};
  D.neighbors = {&A, &C, &H};
  E.neighbors = {&A, &F, &H};
  F.neighbors = {&B, &E, &G};
  G.neighbors = {&C, &F, &H};
  H.neighbors = {&D, &E, &G};

  std::vector<Node*> all = {&A, &B, &C, &D, &E, &F, &G, &H};
  for (Node* node : all) {
    TruncateNode(node);
  }

  std::vector<Node*> last;

  for (Node* node : all) {
    if (node->value != 0) {
      last.insert(last.end(), node);
    }
  }

  if (last.empty()) {
    return 0;
  }

  Fix(last[0]);
}