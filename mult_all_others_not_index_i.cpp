// Given an array of integers, return a new array such that each element at index
// i of the new array is the product of all the numbers in the original array
// except the one at i.

#include <climits>
#include <iostream>

void exclusiveProduct(int arr[], int n) {
  long product = 1;
  for (int i = 0; i < n; ++i) {
    product *= arr[i];
  }

  if (product > INT_MAX) {
    product = INT_MAX;
  }

  for (int i = 0; i < n; ++i) {
    arr[i] = product / arr[i];
  }
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  exclusiveProduct(arr, 5);
  for (int i = 0; i < 5; ++i) {
    std::cout << arr[i] << '\n';
  }
}
