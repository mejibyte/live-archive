/*
  Time limit exceeded.

  Correct output but it's too slow.
  (Dijkstra's algorithm)
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
const int oo = INT_MAX / 4;
int X, Y;
bool can_jump[1000][1000];
int d[1000][1000];

#define valid(x, y) (0 <= x && x < X && 0 <= y && y < Y && can_jump[x][y])

typedef pair<int, pair<int, int> > state;

int dijkstra(int sx, int sy, int ex, int ey){
  set<state> q;

  d[sx][sy] = 0;
  q.insert(make_pair(0, make_pair(sx, sy)));

  while (q.size()){
    const int w = q.begin()->first,
      x = q.begin()->second.first, y = q.begin()->second.second;
    q.erase(q.begin());

    if (w > d[x][y]) continue;
    if (x == ex && y == ey) break;

    for (int dx=-2; dx<=2; ++dx){
      for (int dy=-2; dy<=2; ++dy){
        if (dx || dy){ //avoid (0,0)
          int nx = x + dx;
          int ny = y + dy;
          if (!valid(nx, ny)) continue;

          int w_extra = abs(x-nx)+abs(y-ny)+1+2*(abs(x-nx)==2 || abs(y-ny)==2);
          //printf("from (%d, %d) can go to (%d, %d) using %d\n", x, y, nx, ny, w_extra);
          if (w + w_extra < d[nx][ny]){
            d[nx][ny] = w + w_extra;
            q.insert(make_pair(w + w_extra, make_pair(nx, ny)));
          }
        }
      }
    }
  }

  return d[ex][ey];
}

int main(){
  while (scanf("%d %d", &X, &Y)==2 && X && Y){
    //cleaning
    for (int x=0; x<X; ++x)
      for (int y=0; y<Y; ++y){
        d[x][y] = oo;
      }
    memset(can_jump, 1, sizeof can_jump); //this seems to be faster than making the loop

    int sx, sy, ex, ey; //start && end coordinates
    scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
    --sx, --sy, --ex, --ey;
    int w;
    for (scanf("%d", &w); w--; ){
      int ax, ay, bx, by;
      scanf("%d %d %d %d", &ax, &ay, &bx, &by);
      --ax, --ay, --bx, --by;
      for (int x=ax; x<=bx; ++x)
        for (int y=ay; y<=by; ++y)
          can_jump[x][y] = false;
    }


    /*
    for (int y=Y-1; y>=0; --y, printf("\n"))
      for (int x=0; x<X; ++x)
        printf("%d", can_jump[x][y]);
    printf("\n");
    printf("%d\n", d[0][0]);
    */

    int t = dijkstra(sx, sy, ex, ey);
    if (t < oo) printf("%d\n", t);
    else printf("impossible\n");

  }
  return 0;
}
