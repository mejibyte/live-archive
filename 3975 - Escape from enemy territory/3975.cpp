/*
  Time limit exceeded.
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
  int i, j, w, d;
  state(){}
  state(int I, int J, int W, int _D = -1) : i(I), j(J), w(W), d(_D){}
};

int main(){
  int C;
  scanf("%d", &C);
  while (C--){
    int n;
    scanf("%d %d %d", &n, &X, &Y);
    int si, sj, fi, fj;
    scanf("%d %d %d %d", &si, &sj, &fi, &fj);

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
    queue<state> q;
    q.push(state(si, sj, 0, D[si][sj]));
    v[si][sj] = D[si][sj];
    while (q.size()){
      state u = q.front();
      int i = u.i, j = u.j, w = u.w, d = u.d;
      q.pop();

      if (i == fi && j == fj){
        if (d > ans_d || (d == ans_d && w < ans_w)){
          ans_d = d;
          ans_w = w;
        }
      }
      //printf("popped (%d, %d, %d, %d)\n", i, j, w, d);
      if (d < v[i][j]) continue;
      for (int k=0; k<4; ++k){
        int ni = i + di[k], nj = j + dj[k];
        if (inside(ni, nj)){
          int new_d = d <? D[ni][nj];
          if (new_d > v[ni][nj]){
            v[ni][nj] = new_d;
            q.push(state(ni, nj, w+1, new_d));
          }
        }
      }
    }
    printf("%d %d\n", ans_d, ans_w);
  }
  return 0;
}
