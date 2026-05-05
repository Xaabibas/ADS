#include <deque>
#include <iostream>

class CustomQueue {
private:
  std::deque<int> head_;
  std::deque<int> tail_;

  void Balance() {
    int temp = tail_.front();
    tail_.pop_front();
    head_.push_back(temp);
  }

public:
  void Pop() {
    head_.pop_front();
    if (head_.size() < tail_.size()) {
      Balance();
    }
  }

  [[nodiscard]] int Top() const {
    return head_.front();
  }

  void PushBack(int value) {
    tail_.push_back(value);

    if (tail_.size() > head_.size()) {
      Balance();
    }
  }

  void PushCenter(int value) {
    if (head_.size() > tail_.size()) {
      tail_.push_front(value);
    } else {
      head_.push_back(value);
    }
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  std::string sym;
  CustomQueue queue;

  for (int i = 0; i < n; i++) {
    std::cin >> sym;

    if (sym == "+") {
      int value = 0;
      std::cin >> value;
      queue.PushBack(value);
    } else if (sym == "*") {
      int value = 0;
      std::cin >> value;
      queue.PushCenter(value);
    } else {
      int top = queue.Top();
      queue.Pop();
      std::cout << top << "\n";
    }
  }
}