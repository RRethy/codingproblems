// Given a list of numbers and a number k, return whether any two numbers from the
// list add up to k.

#include <set>
#include <iostream>

bool doTwoNumbersSumToK(int *arr, int n, int k) {
  std::set<int> seen;
  for (int i = 0; i < n; ++i) {
    if (seen.count(k - arr[i]) > 0) {
      return true;
    } else {
      seen.emplace(arr[i]);
    }
  }
  return false;
}

int main() {
  int arr[] = {10, 15, 3, 7};
  std::cout << doTwoNumbersSumToK(arr, 4, 17) << '\n';
  std::cout << doTwoNumbersSumToK(arr, 4, 19) << '\n';
}
