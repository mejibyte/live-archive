/*
  Wrong answer + time limit exceeded
 */
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <stdio.h>

using namespace std;

struct point{
  int i, j, h;
  point(){} point(int i, int j, int h = -1) : i(i), j(j), h(h) {}
  bool operator < (const point &that) const { return h < that.h; }
};

point p[501*501];
int g[501][501];
bool possible[501][501];
bool visited[501][501];

#define inside(i, j) (0 <= i && i < r && 0 <= j && j < c)

int main(){
  int cases;
  scanf("%d", &cases);
  while (cases--){
    int r, c, d, n = 0;
    scanf("%d %d %d", &r, &c, &d);
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
        scanf("%d", &g[i][j]);
        p[n++] = point(i, j, g[i][j]);
        possible[i][j] = true;
      }
    }
    sort(p, p+n);

    int ans = 0;
    for (int k=n-1; k>=0; --k){
      int a = p[k].i, b = p[k].j, H = p[k].h;
      if (possible[a][b]){
        memset(visited, 0, sizeof visited);
        //printf("trying (%d, %d) = %d\n", a, b, H);
        int reps = 1; //Repetitions
        queue<point> q;
        q.push(point(a, b));
        while (q.size()){
          int i = q.front().i, j = q.front().j, h = g[i][j];
          q.pop();

          //printf("  popped (%d, %d) = %d\n", i, j, h);

          if (visited[i][j]) continue;
          visited[i][j] = true;

          if (!possible[i][j]){
            if (H - h < d){
              possible[a][b] = false;
            }
            continue;
          }

          if (i != a || j != b){
            possible[i][j] = false;
            if (h == H) reps++;
          }

          for (int di=-1; di<=1; ++di){
            for (int dj=-1; dj<=1; ++dj){
              if ((di || dj) && (!di || !dj)){
                int ni = i + di, nj = j + dj;
                if (inside(ni, nj)){
                  if (!visited[ni][nj] && (h >= g[ni][nj] || H == g[ni][nj])){
                    q.push(point(ni, nj));
                    //printf("     pushed (%d, %d) = %d\n", ni, nj, g[ni][nj]);
                  }
                }
              }
            }
          }
        }
        if (possible[a][b]){
          //printf("(%d, %d) = %d belongs to a summit with %d nodes\n", a, b, H, reps);
          ans += reps;
        }else{
          //printf("not.\n");
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
