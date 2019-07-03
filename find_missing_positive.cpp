#include <cstdlib>
#include <iostream>

// Given an array of integers, find the first missing positive integer in
// linear time and constant space. In other words, find the lowest positive
// integer that does not exist in the array. The array can contain duplicates
// and negative numbers as well.

int partition(int arr[], int n) {
  int j = 0;
  for (int i = 0; i < n; ++i) {
    if (arr[i] <= 0) {
      int tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
      j++;
    }
  }
  return j;
}

int findMissingPositive(int arr[], int n) {
  for (int i = 0; i < n; ++i) {
    int num = abs(arr[i]);
    if (num > n || arr[num - 1] < 0) continue;
    arr[num - 1] = -1 * arr[num - 1];
  }
  for (int i = 0; i < n; ++i) {
    if (arr[i] > 0) return i + 1;
  }
  return n + 1;
}

int main() {
  int arr1[] = { 3, 4, -1, 1 };
  int arr2[] = { 1, 2, 0 };
  int arr3[] = { 1, 2, 3 };
  int shift1 = partition(arr1, 4);
  int shift2 = partition(arr2, 3);
  int shift3 = partition(arr3, 3);
  std::cout << findMissingPositive(arr1 + shift1, 4 - shift1) << '\n';
  std::cout << findMissingPositive(arr2 + shift2, 3 - shift2) << '\n';
  std::cout << findMissingPositive(arr3 + shift3, 3 - shift3) << '\n';
}
