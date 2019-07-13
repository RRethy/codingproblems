#include <iostream>
#include <string>
#include <map>

using namespace std;

string longestKDistinctSubstring(string &str, unsigned int k) {
  map<char, int> seen;
  unsigned int maxStartI = 0;
  unsigned int size = 0;
  unsigned int l = 0;
  unsigned int r = 0;
  while (r < str.size()) {
    if (seen.count(str[r]) == 0 && seen.size() == k) {
      seen[str[l]]--;
      if (seen[str[l]] == 0) seen.erase(str[l]);
      l++;
    } else {
      if (seen.count(str[r]) == 0) seen[str[r]] = 0;
      seen[str[r]]++;
      r++;
    }

    if (r - l > size) {
      size = r - l;
      maxStartI = l;
    }
  }
  return str.substr(maxStartI, size);
}

int main() {
  string str = "abcbbaaa";
  cout << longestKDistinctSubstring(str, 2) << '\n';
}
