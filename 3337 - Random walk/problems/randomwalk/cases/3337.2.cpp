/*
  Wrong answer
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <stdio.h>

#define V(x) copy(x.begin(), x.end(), ostream_iterator<int>(cout, " ")); cout << endl
#define X first
#define Y second
using namespace std;
typedef pair<int, int> point;

inline double dist_origin(point a){ return sqrt(a.X*a.X + a.Y*a.Y); }

int main(){
  int n;
  while (cin >> n && n){
    vector<point> v(n);
    for (int i=0; i<n; ++i) cin >> v[i].X >> v[i].Y;
    point p = v[0];

    for (int i=1; i<n; ++i){
      point t = make_pair(p.X +  v[i].X, p.Y + v[i].Y);
      double d = dist_origin(t);

      double new_best_dist = d;
      point new_best_point = t;

      t = make_pair(p.X - v[i].X, p.Y - v[i].Y);
      d = dist_origin(t);

      if (d > new_best_dist){
        new_best_dist = d;
        new_best_point = t;
      }

      p = new_best_point;
    }
    printf("Maximum distance = %.3lf meters.\n", dist_origin(p));
  }
  return 0;
}
