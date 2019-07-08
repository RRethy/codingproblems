#include <iostream>

using namespace std;

int largestSumNonAdjacent(int arr[], int n) {
  if (n == 0) return 0;
  if (n == 1) return arr[0];

  int max1 = arr[1];
  int max2 = arr[0];
  for (int i = 2; i < n; ++i) {
    if (max1 < max2) {
      max1 = max2;
    } else {
      max1 ^= max2;
      max2 ^= max1;
      max1 ^= max2;
    }
    if (arr[i] > 0) {
      max1 += arr[i];
    }
  }

  return max1 > max2 ? max1 : max2;
}

int main() {
  int arr1[] = {2, 4, 6, 2, -5};
  cout << largestSumNonAdjacent(arr1, 5) << '\n';
}
