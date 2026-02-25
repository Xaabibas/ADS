#include <iostream>
#include <string>
#include <vector>

const int AlphabetCount = 26;

bool Compare(int letter1, int letter2, std::vector<int>& weight, std::vector<int>& count) {
  if (count[letter1 - 'a'] < 2) {
    return false;
  }
  if (count[letter2 - 'a'] < 2) {
    return true;
  }
  return weight[letter1 - 'a'] > weight[letter2 - 'a'];
}

void Merge(
    std::vector<int>& alphabet,
    int start,
    int mid,
    int end,
    std::vector<int>& weight,
    std::vector<int>& count
) {
  std::vector<int> merged(end - start);
  int index = 0;

  int it1 = start;
  int it2 = mid;

  while (it1 < mid && it2 < end) {
    if (Compare(alphabet[it2], alphabet[it1], weight, count)) {
      merged[index] = alphabet[it2];
      index++;
      it2++;
    } else {
      merged[index] = alphabet[it1];
      index++;
      it1++;
    }
  }

  while (it1 < mid) {
    merged[index] = alphabet[it1];
    index++;
    it1++;
  }
  while (it2 < end) {
    merged[index] = alphabet[it2];
    index++;
    it2++;
  }

  for (int i = 0; i < index; i++) {
    alphabet[start + i] = merged[i];
  }
}

void Sort(
    std::vector<int>& alphabet,
    int start,
    int end,
    std::vector<int>& weight,
    std::vector<int>& count
) {
  if (end - start == 1) {
    return;
  }
  int mid = (end + start) / 2;

  Sort(alphabet, start, mid, weight, count);
  Sort(alphabet, mid, end, weight, count);

  Merge(alphabet, start, mid, end, weight, count);
}

int main() {
  std::string line;
  std::vector<int> weight(AlphabetCount);
  std::vector<int> count(AlphabetCount);
  std::vector<int> alphabet(AlphabetCount);

  std::cin >> line;
  for (char i = 0; i < AlphabetCount; i++) {
    std::cin >> weight[i];
    alphabet[i] = 'a' + i;
  }

  for (char sym : line) {
    count[sym - 'a']++;
  }

  Sort(alphabet, 0, AlphabetCount, weight, count);

  std::string result(line);

  int pointer = 0;

  for (int sym : alphabet) {
    if (count[sym - 'a'] > 1) {
      result[pointer] = static_cast<char>(sym);
      result[line.size() - pointer - 1] = static_cast<char>(sym);
      pointer++;
      count[sym - 'a']--;
      count[sym - 'a']--;
    }
  }

  for (int sym : alphabet) {
    while (count[sym - 'a'] > 0) {
      result[pointer] = static_cast<char>(sym);
      pointer++;
      count[sym - 'a']--;
    }
  }

  std::cout << result << "\n";
}