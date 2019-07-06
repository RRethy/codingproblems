#include <vector>
#include <iostream>

// Given n points on a 2D plane, find the maximum number of points that lie on
// the same straight line.

using namespace std;

class Solution {

  bool isSame(long x1, long y1, long x2, long y2) {
    return x1 == x2 && y1 == y2;
  }

  public:

    int maxPoints(vector<vector<int>> &points) {
      if (points.size() < 2) return points.size();

      int max = 2;
      for (unsigned int i1 = 0; i1 < points.size(); ++i1) {
        int dups = 0;
        int i1Max = 1;
        for (unsigned int i2 = i1 + 1; i2 < points.size(); ++i2) {
          int len = 2;

          long x1 = points[i1][0];
          long y1 = points[i1][1];
          long x2 = points[i2][0];
          long y2 = points[i2][1];

          if (isSame(x1, y1, x2, y2)) {
            dups++;
            continue;
          }

          for (unsigned int i3 = 0; i3 < points.size(); ++i3) {
            if (i3 == i1 || i3 == i2) continue;

            long x3 = points[i3][0];
            long y3 = points[i3][1];

            if (isSame(x1, y1, x3, y3)) continue;
            if (isSame(x2, y2, x3, y3)) {
              len++;
              continue;
            }

            if (((y3-y1)*(x2-x1)) == ((x3-x1)*(y2-y1))) {
              len++;
            }
          }

          if (len > i1Max) i1Max = len;
        }
        i1Max += dups;
        if (i1Max > max) max = i1Max;
      }

      return max;
    }
};

int main() {
  Solution soln;
  // vector<vector<int>> points = {{0,0},{1,1},{0,0}};
  // vector<vector<int>> points = {{0,0},{0,0},{0,0}};
  vector<vector<int>> points = {{1,1},{3,2},{5,3},{4,1},{2,3},{1,4},{1,4}};
  // vector<vector<int>> points = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
  cout << soln.maxPoints(points) << '\n';
}
