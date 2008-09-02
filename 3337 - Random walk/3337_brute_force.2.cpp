/*
  Imprimir los puntos alcanzables sorteados por distancia
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

#define X first
#define Y second
using namespace std;
typedef pair<int, int> point;

inline double dist_origin(point a){ return sqrt(a.X*a.X + a.Y*a.Y); }

bool pancake(const point &a, const point &b){
  return dist_origin(a) + 1e-9 < dist_origin(b);
}

vector<point> answer;
int n;
point v[101];

void backtrack(int i, int x, int y){
  if (i == n){
    answer.push_back(point(x, y));
  }else{
    backtrack(i+1, x+v[i].X, y+v[i].Y);
    backtrack(i+1, x-v[i].X, y-v[i].Y);
  }
}

int main(){

  while (cin >> n && n){
    for (int i=0; i<n; ++i){
      cin >> v[i].X >> v[i].Y;
      cout << " . " << v[i].X << ", " << v[i].Y << endl;
    }
    answer.clear();
    backtrack(0, 0, 0);
    sort(answer.begin(), answer.end(), pancake);
    for (int i=0; i<answer.size(); ++i){
      printf("Reachable point (%d, %d). Distance = %.3lf\n", answer[i].X, answer[i].Y, dist_origin(answer[i]));
    }
    printf("Maximum distance = %.3lf meters.\n", dist_origin(answer.back()));
  }
  return 0;
}
