#include <iostream>

using namespace std;

int main() {
  int a = 4;
  int b = 10;
  a ^= b;
  b ^= a;
  a ^= b;
  cout << a << '\n';
  cout << b << '\n';
}
