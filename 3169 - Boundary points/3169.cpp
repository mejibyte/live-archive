/*
  Problem: 3169 - Boundary points
  Algorithm: Convex hull; Andrew's monotone chain.
  Author: Andrés Mejía-Posada
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
using namespace std;

struct point {
  double x, y;
  point(){} point(double x, double y) : x(x), y(y) {}
  bool operator <(const point &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
};
 
// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
double cross(const point &O, const point &A, const point &B){
  double d = (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
  if (fabs(d) < 1e-9) return 0.0;
  return d;
}
 
// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<point> convexHull(vector<point> P){
  int n = P.size(), k = 0;
  vector<point> H(2*n);
  
  // Sort points lexicographically
  sort(P.begin(), P.end());
  
  // Build lower hull
  for (int i = 0; i < n; i++) {
    while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0.0) k--;
    H[k++] = P[i];
  }
  
  // Build upper hull
  for (int i = n-2, t = k+1; i >= 0; i--) {
    while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0.0) k--;
    H[k++] = P[i];
  }
  
  H.resize(k);
  return H;
}

int main(){
  string s;
  while (getline(cin, s)){
    stringstream splitter(s);
    string pnt;
    vector<point> poly;
    while (splitter >> pnt){
      assert(pnt.size() > 3);
      pnt[0] = pnt[pnt.size()-1] = pnt[pnt.find(',')] = ' ';
      stringstream sin(pnt);
      double x, y;
      sin >> x >> y;
      poly.push_back(point(x, y));
    }

    vector<point> ans = convexHull(poly);
    cout << "(" << ans.front().x << "," << ans.front().y << ")";
    for (int i=1; i<ans.size(); ++i){
      cout << " (" << ans[i].x << "," << ans[i].y << ")";
    }
    cout << endl;
  }
  return 0;
}
