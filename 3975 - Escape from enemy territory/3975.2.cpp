/*
  Accepted.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
using namespace std;

const int inf = (1 << 29);

int di[] = {-1, +1, +0, +0};
int dj[] = {+0, +0, -1, +1};

int X, Y, D[1100][1100], v[1100][1100];

#define inside(i, j)(0 <= i && i < X && 0 <= j && j < Y)

struct state{
  int i, j, w;
  state(){}
  state(int I, int J, int W) : i(I), j(J), w(W) {}
  bool operator < (const state &that) const { return w < that.w; }
};

int main(){
  int C;
  scanf("%d", &C);
  while (C--){
    int n;
    scanf("%d %d %d", &n, &X, &Y);
    int si, sj, fi, fj;
    scanf("%d %d %d %d", &si, &sj, &fi, &fj);


    /*
      Encontrar la distancia más corta entre cualquier bomba y cualquier casilla.
      El resultado queda en la matriz D.
      D[i][j] = mínima distancia entre la casilla (i,j) y alguna bomba.
     */
    for (int i=0; i<X; ++i){
      for (int j=0; j<Y; ++j){
        D[i][j] = inf;
      }
    }
    queue<state> pq;
    while (n--){
      int i, j;
      scanf("%d %d", &i, &j);
      D[i][j] = 0;
      pq.push(state(i, j, 0));
    }
    while (pq.size()){
      state u = pq.front();
      int i = u.i, j = u.j, w = u.w;
      pq.pop();
      if (w > D[i][j]) continue;
      for (int k=0; k<4; ++k){
        int ni = i + di[k], nj = j + dj[k];
        if (inside(ni, nj) && D[ni][nj] > w + 1){
          D[ni][nj] = w + 1;
          pq.push(state(ni, nj, w+1));
        }
      }
    }

    /*
      for (int i=0; i<X; ++i){
      for (int j=0; j<Y; ++j){
      cerr << D[i][j] << " ";
      }
      cerr << endl;
      }
    */

    int ans_d = -inf, ans_w = inf;
    for (int i=0; i<X; ++i){
      for (int j=0; j<Y; ++j){
        v[i][j] = -inf;
      }
    }
    priority_queue<state> q;
    q.push(state(si, sj, D[si][sj]));
    v[si][sj] = D[si][sj];
    while (q.size()){
      state u = q.top();
      int i = u.i, j = u.j, w = u.w;
      q.pop();

      if (i == fi && j == fj){
        ans_d = w;
        break;
      }
      if (w < v[i][j]) continue;
      //printf("popped (%d, %d, %d, %d)\n", i, j, w, d);

      for (int k=0; k<4; ++k){
        int ni = i + di[k], nj = j + dj[k];
        if (inside(ni, nj)){
          int new_d = w <? D[ni][nj];
          if (new_d > v[ni][nj]){
            v[ni][nj] = new_d;
            q.push(state(ni, nj, new_d));
          }
        }
      }
    }

    while (pq.size()) pq.pop();
    for (int i=0; i<X; ++i){
      for (int j=0; j<Y; ++j){
        v[i][j] = 0;
      }
    }
    pq.push(state(si, sj, 0));
    while (pq.size()){
      state u = pq.front(); pq.pop();
      if (v[u.i][u.j]) continue;
      v[u.i][u.j] = true;
      if (u.i == fi && u.j == fj){
        ans_w = u.w;
        break;
      }
      for (int k=0; k<4; ++k){
        int ni = u.i + di[k], nj = u.j + dj[k];
        if (inside(ni, nj) && !v[ni][nj] && D[ni][nj] >= ans_d){
          pq.push(state(ni, nj, u.w + 1));
        }
      }

    }
    printf("%d %d\n", ans_d, ans_w);
  }
  return 0;
}
