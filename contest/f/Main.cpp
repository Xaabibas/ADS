#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool Compare(const std::string& string1, const std::string& string2) {
  std::string string12;
  string12.append(string1).append(string2);
  std::string string21;
  string21.append(string2).append(string1);

  return string12 > string21;
}

int main() {
  std::vector<std::string> data;
  std::string line;

  while (std::cin >> line) {
    if (!line.empty()) {
      data.push_back(line);
    }
  }

  for (std::string& str : data) {
    std::cout << str << "\n";
  }

  std::sort(begin(data), end(data), Compare);

  for (std::string& str : data) {
    std::cout << str;
  }
}