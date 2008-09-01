#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <stdio.h>

#define X first
#define Y second
using namespace std;
typedef pair<int, int> point;

inline double dist_origin(point a){ return sqrt(a.X*a.X + a.Y*a.Y); }

double answer;
int n;
point v[101];

void backtrack(int i, int x, int y){
  if (i == n){
    printf("Reachable point (%d, %d) in %d steps. Distance = %.3lf\n", x, y, i, dist_origin(make_pair(x, y)));
    answer = max(answer, dist_origin(make_pair(x, y)));
  }else{
    backtrack(i+1, x+v[i].X, y+v[i].Y);
    backtrack(i+1, x-v[i].X, y-v[i].Y);
  }
}

int main(){

  while (cin >> n && n){
    for (int i=0; i<n; ++i) cin >> v[i].X >> v[i].Y;
    answer = 0.0;
    backtrack(0, 0, 0);
    printf("Maximum distance = %.3lf meters.\n", answer);
  }
  return 0;
}
