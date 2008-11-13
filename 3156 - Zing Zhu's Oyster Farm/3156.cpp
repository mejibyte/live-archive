/*
  Problem: 3156 - Zing Zhu's Oyster Farm
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)


  Time limit exceeded + WA
 */

using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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

#define D(x) cout << #x " is " << x << endl

#define maximize(i, x) if (i < (x)) i = (x);
#define minimize(i, x) if (i > (x)) i = (x);

bool water[1010][1010];
short walls[1010][1010][4];

//sumar a todas las coordenadas para que no haya negativos
const int add = 503;
int n, ans;

int min_x, min_y, max_x, max_y;

enum {Up, Right, Down, Left};

struct point{
  int x, y;
  point(){} point(int X, int Y) : x(X), y(Y) {}
};


bool valid(int x, int y){
  return !( ( x < min_x-1 || y < min_y-1 || x > max_x + 1 || y > max_y + 1 || water[x][y] ) );
}

inline void encolar(int x, int y, queue<point> &q){
  if (valid(x, y)) q.push(point(x, y));
}

void flood(int x, int y, int w){
  queue<point> q;
  q.push(point(x, y));

  while (q.size()){
    int x = q.front().x, y = q.front().y;

    q.pop();

    //D(x), D(y);

    if (!valid(x, y)) continue;

    water[x][y] = true;

    if (walls[x][y][Up] < w) encolar(x, y+1, q);
    if (walls[x][y][Down] < w) encolar(x, y-1, q);
    if (walls[x][y][Right] < w) encolar(x+1, y, q);
    if (walls[x][y][Left] < w) encolar(x-1, y, q);
  }

}


int main(){
  while ( scanf("%d", &n) == 1 && n ){
    memset(water, 0, sizeof water);
    memset(walls, 0, sizeof walls);

    max_x = INT_MIN, max_y = INT_MIN;
    min_x = INT_MAX, min_y = INT_MAX;

    for (int i=0; i<n; ++i){
      int x1, y1, x2, y2, h;
      scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &h);

      x1 += add, y1 += add, x2 += add, y2 += add;

      maximize(max_x, x1);
      maximize(max_x, x2);

      maximize(max_y, y1);
      maximize(max_y, y2);


      minimize(min_x, x1);
      minimize(min_x, x2);

      minimize(min_y, y1);
      minimize(min_y, y2);


      if (x1 == x2){
        if (y2 < y1) swap(y1, y2);
        for (int y=y1; y<=y2; ++y){
          maximize(walls[x1-1][y][Right], h);
          maximize(walls[x1][y][Left], h);
        }
      }else{ //y1 == y2

        if (x2 < x1) swap(x1, x2);
        for (int x=x1; x<=x2; ++x){
          maximize(walls[x][y1-1][Up], h);
          maximize(walls[x][y1][Down], h);
        }
      }
    }

    /*
    D(min_x);
    D(min_y);
    D(max_x);
    D(max_y);
    */

    int w;
    scanf("%d", &w);
    flood(min_x-1, min_y-1, w);

    ans = 0;
    for (int i= min_x-1; i <= max_x+1; ++i){
      for (int j= min_y-1; j <= max_y+1; ++j){
        ans += !water[i][j];
      }
    }

    D(n);
    printf("%d\n", ans);

  }
  return 0;
}

/*
  Challenge:

  4
  0 2 1 2 10
  0 1 1 1 10
  1 0 1 1 10
  2 0 2 1 10
  1

 */
