#include <iostream>
#include <climits>
#include <string>

using namespace std;

int reverse(unsigned long long n, unsigned long long acc) {
  if (n < 10) return acc*10 + n%10;

  return reverse(n/10, acc*10 + n%10);
}

bool isPalindrome(unsigned long long n) {
  return n == reverse(n, 0);
}

class Solution {

  public:
    string nearestPalindromic(string numstr) {
      if (numstr.size() == 1) {
        int n = numstr[0] - '0';
        return n == 0 ? "1" : to_string(n-1);
      }

      for (unsigned int i = 0; i < numstr.size()/2; ++i) {
        numstr[numstr.size() - i - 1] = numstr[i];
      }
      return numstr;
    }
};

int main() {
  Solution soln;
  // "2442" 2400 2500 2442 2552 2332:O
  cout << soln.nearestPalindromic("124") << '\n';
  cout << soln.nearestPalindromic("121") << '\n';
  cout << soln.nearestPalindromic("119") << '\n';
  cout << soln.nearestPalindromic("1") << '\n';
  cout << soln.nearestPalindromic("0") << '\n';
  cout << soln.nearestPalindromic("807045053224792883") << '\n';
  cout << stoll("807045053224792883") << '\n';
  // cout << isPalindrome(5) << '\n';
  // cout << isPalindrome(19) << '\n';
  // cout << isPalindrome(22) << '\n';
  // cout << isPalindrome(222) << '\n';
  // cout << isPalindrome(212) << '\n';
  // cout << isPalindrome(113123123) << '\n';
  // cout << isPalindrome(123454321) << '\n';
}
