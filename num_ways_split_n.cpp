#include <set>
#include <iostream>

using namespace std;

// can use caching to improve speed
int numWays(set<int> atoms, int N) {
  if (N == 0) return 1;
  if (N < 0) return 0;
  int num = 0;
  for (auto &atom : atoms) {
    num += numWays(atoms, N-atom);
  }
  return num;
}

int main() {
  cout << numWays({1, 2}, 4);
}
