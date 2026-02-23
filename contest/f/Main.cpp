#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool Compare(const std::string& string1, const std::string& string2) {
  int k = std::min(string1.size(), string2.size());

  for (int i = 0; i < k; i++) {
    if (string1[i] > string2[i]) {
      return true;
    }
    if (string2[i] > string1[i]) {
      return false;
    }
  }

  return string1.size() > string2.size();
}

int main() {
  std::pmr::vector<std::string> data;
  std::string line;

  while (std::getline(std::cin, line)) {
    if (line == "exit") {
      break;
    }
    data.push_back(line);
  }

  std::sort(begin(data), end(data), Compare);

  for (std::string& str : data) {
    std::cout << str;
  }
}