#include <climits>
#include <iostream>
#include <map>
#include <utility>

struct Node {
  int a;
  int size;

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

class Treap {
private:
  Node* root_;
  int n_;

  std::pair<Node*, Node*> Split(Node* node, int key) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (key > node->a) {
      auto rec = Split(node->right, key);
      node->right = rec.first;
      return {node, rec.second};
    }
    auto rec = Split(node->left, key);
    node->left = rec.second;
    return {rec.first, node};
  }

  Node* Merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->size > right->size) {
      left->right = Merge(left->right, right);
      return left;
    }
    right->left = Merge(left, right->left);
    return right;
  }

  void Insert(int a, int size) {
    Node* node = new Node{a, size, nullptr, nullptr};
    auto pair = Split(root_, a);
    root_ = Merge(pair.first, node);
    root_ = Merge(root_, pair.second);
  }

  void Remove(int a) {
    auto pair1 = Split(root_, a);
    auto pair2 = Split(pair1.second, a + 1);

    root_ = Merge(pair1.first, pair2.second);

    Delete(pair2.first);
  }

  Node* Search(Node* node, int request) {
    if (node == nullptr) {
      return nullptr;
    }
    Node* left = node->left;
    if (left == nullptr || left->size < request) {
      return node;
    }
    return Search(left, request);
  }

  Node* FindA(int a, Node* node) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->a == a) {
      return node;
    }
    Node* left = node->left;
    Node* right = node->right;
    if (node->a < a) {
      return FindA(a, right);
    }
    return FindA(a, left);
  }

  Node* FindB(int b, Node* node) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->a + node->size == b) {
      return node;
    }
    Node* left = node->left;
    Node* right = node->right;
    if (node->a + node->size < b) {
      return FindB(b, right);
    }
    return FindB(b, left);
  }

public:
  explicit Treap(int n) : root_(new Node{}), n_(n) {
    root_->a = 0;
    root_->size = n_;
    root_->left = nullptr;
    root_->right = nullptr;
  }

  ~Treap() {
    Delete(root_);
  }

  int Allocate(int request) {
    if (root_ == nullptr || root_->size < request) {
      return -1;
    }

    Node* result = Search(root_, request);

    if (result->size > request) {
      Insert(result->a + request, result->size - request);
    }
    int res = result->a;
    Remove(result->a);

    return res + 1;
  }

  void Free(int a, int request) {
    Node* free_left = FindB(a, root_);
    Node* free_right = FindA(a + request, root_);

    if (free_left != nullptr) {
      a = free_left->a;
      request += free_left->size;
      Remove(free_left->a);
    }
    if (free_right != nullptr) {
      request += free_right->size;
      Remove(free_right->a);
    }

    Insert(a, request);
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;

  std::map<int, std::pair<int, int>> map;

  auto treap = Treap(n);

  for (int i = 0; i < m; i++) {
    int request = 0;
    std::cin >> request;

    if (request > 0) {
      int result = treap.Allocate(request);
      if (result != -1) {
        map[i] = {result - 1, request};
      }
      std::cout << result << "\n";
    } else {
      int index = -request - 1;
      if (map.contains(index)) {
        auto prev = map[index];
        treap.Free(prev.first, prev.second);
      }
    }
  }
}