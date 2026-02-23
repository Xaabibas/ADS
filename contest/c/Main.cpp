#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>

void SplitLine(std::string& line, std::string& variable1, std::string& variable2) {
  bool eq = false;
  for (char c : line) {
    if (c == '=') {
      eq = true;
      continue;
    }

    if (eq) {
      variable2 += c;
    } else {
      variable1 += c;
    }
  }
}

void ProcessLine(
    std::map<std::string, std::stack<int>>& map, std::string& line, std::queue<std::string>& queue
) {
  std::string variable1;
  std::string variable2;

  SplitLine(line, variable1, variable2);

  try {
    int number;
    number = std::stoi(variable2);
    map[variable1].push(number);
  } catch (const std::invalid_argument& e) {
    std::stack<int> history = map[variable2];
    int value;
    if (history.empty()) {
      value = 0;
    } else {
      value = history.top();
    }
    map[variable1].push(value);

    std::cout << value << "\n";
  }
  queue.push(variable1);
}

int main() {
  std::map<std::string, std::stack<int>> map;
  std::string line;
  std::stack<std::queue<std::string>> stack;
  stack.push(std::queue<std::string>());

  while (std::getline(std::cin, line)) {
    if (line == "{") {
      stack.push(std::queue<std::string>());
      continue;
    }
    if (line == "}") {
      std::queue<std::string> queue = stack.top();

      while (!queue.empty()) {
        std::string variable = queue.front();
        queue.pop();
        map[variable].pop();
      }

      stack.pop();
      continue;
    }
    ProcessLine(map, line, stack.top());
  }
}