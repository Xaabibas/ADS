#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

int main() {
  std::stack<char> stack;
  std::stack<int> traps;
  int traps_cnt = 0;
  std::stack<int> animals;
  int animal_cnt = 1;

  std::string plan;
  std::cin >> plan;
  int n = plan.size() / 2;
  std::vector<int> indexes(n);

  for (char i : plan) {
    if (islower(i)) {
      animals.push(animal_cnt++);
    } else {
      traps.push(traps_cnt++);
    }

    if (stack.empty()) {
      stack.push(i);
      continue;
    }

    char top = stack.top();

    if (toupper(i) == toupper(top) && i != top) {
      indexes[traps.top()] = animals.top();
      traps.pop();
      animals.pop();
      stack.pop();
    } else {
      stack.push(i);
    }
  }

  if (stack.empty()) {
    std::cout << "Possible\n";
    for (int i : indexes) {
      std::cout << i << " ";
    }
  } else {
    std::cout << "Impossible\n";
  }
}
