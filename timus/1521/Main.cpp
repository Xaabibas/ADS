#include <iostream>

struct Node {
  int a;
  int b;

  int sum;

  Node* left;
  Node* right;
};

void Delete(Node* node) {
  if (node == nullptr) {
    return;
  }
  Delete(node->left);
  Delete(node->right);

  delete node;
}

class Tree {
private:
  Node* root_{};

  Node* Build(int a, int b) {
    Node* node = new Node{};
    node->a = a;
    node->b = b;
    node->sum = b - a;
    node->left = nullptr;
    node->right = nullptr;
    if (b - a == 1) {
      return node;
    }
    int mid = (b + a) / 2;

    node->left = Build(a, mid);
    node->right = Build(mid, b);

    return node;
  }

  int Remove(int x, Node* node) {
    node->sum--;
    if (node->b - node->a == 1) {
      return node->a;
    }
    Node* left = node->left;
    Node* right = node->right;

    if (left->sum > x) {
      return Remove(x, left);
    }

    return Remove(x - left->sum, right);
  }

public:
  explicit Tree(int n) : root_(Build(0, n)) {
  }

  ~Tree() {
    Delete(root_);
  }

  int Size() {
    return root_->sum;
  }

  int Cut(int x) {
    return Remove(x, root_);
  }
};

int main() {
  int n = 0;
  int k = 0;

  std::cin >> n >> k;

  int pos = 0;

  Tree tree = Tree(n);

  for (int i = 0; i < n; i++) {
    pos = (pos + k - 1) % tree.Size();

    int res = tree.Cut(pos);
    std::cout << res + 1 << " ";
  }
}