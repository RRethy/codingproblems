#include <string>
#include <iostream>
#include <map>

using namespace std;

// Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count
// the number of ways it can be decoded.

// For example, the message '111' would give 3, since it could be decoded as
// 'aaa', 'ka', and 'ak'.

map<int, int> seen;

int num_ways(const char *msg, int len, int k) {
  if (k >= len) return 1;

  if (seen.count(k) > 0) return seen[k];

  int num = num_ways(msg, len, k+1);
  seen[k+1] = num;
  if (k + 1 < len) {
    const char d1 = *(msg + k);
    const char d2 = *(msg + k + 1);
    int composite = ((d1 - '0') * 10) + (d2 - '0');
    if (composite > 0 && composite <= 26) {
      int num2 = num_ways(msg, len, k+2);
      seen[k+2] = num2;
      num += num2;
    }
  }
  return num;
}

int main() {
  const char *msg1 = "111";
  const char *msg2 = "9121";
  const char *msg3 = "1212";
  const char *msg4 = "24161212172912628128";
  cout << num_ways(msg1, 3, 0) << '\n';
  seen = {};
  cout << num_ways(msg2, 4, 0) << '\n';
  seen = {};
  cout << num_ways(msg3, 4, 0) << '\n';
  seen = {};
  cout << num_ways(msg4, 20, 0) << '\n';
}
