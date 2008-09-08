/*
  Accepted.
  (Lentico! Casi de último con 9.4 segundos)
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

queue<state> q;
priority_queue<state> pq;

int main(){
  int C;
  scanf("%d", &C);
  while (C--){
    int n;
    scanf("%d %d %d", &n, &X, &Y);
    int si, sj, fi, fj; //start_i, start_j, final_i, final_j
    scanf("%d %d %d %d", &si, &sj, &fi, &fj);


    /*
      Encontrar la distancia más corta entre cualquier bomba y cualquier casilla, usando BFS.
      El resultado queda en la matriz D.
      D[i][j] = mínima distancia entre la casilla (i,j) y alguna bomba.
     */
    for (int i=0; i<X; ++i){
      for (int j=0; j<Y; ++j){
        D[i][j] = inf;
      }
    }

    q = queue<state>();
    while (n--){
      int i, j;
      scanf("%d %d", &i, &j);
      D[i][j] = 0;
      q.push(state(i, j, 0));
    }
    while (q.size()){
      state u = q.front();
      q.pop();
      if (u.w > D[u.i][u.j]) continue;
      for (int k=0; k<4; ++k){
        int ni = u.i + di[k], nj = u.j + dj[k];
        if (inside(ni, nj) && D[ni][nj] > u.w + 1){
          D[ni][nj] = u.w + 1;
          q.push(state(ni, nj, u.w+1));
        }
      }
    }


    int ans_d = -inf, ans_w = inf;
    for (int i=0; i<X; ++i){
      for (int j=0; j<Y; ++j){
        v[i][j] = -inf;
      }
    }
    /*
      Encontrar el camino que tenga máximo elemento mínimo entre start y end.
      Lo hago usando Dijkstra, igual a como resolví el problema 10099 - Tourist guide
      de la UVa.
      El resultado queda en ans_d = elemento máximo del camino con máximo elemento mínimo ;)
      En otras palabras, ans_d es el primer número de la salida.
     */
    pq = priority_queue<state>();
    pq.push(state(si, sj, D[si][sj]));
    v[si][sj] = D[si][sj];
    while (pq.size()){
      state u = pq.top();
      pq.pop();

      if (u.i == fi && u.j == fj){
        ans_d = u.w;
        break; //Fundamental, esto es lo que hace que el algoritmo sea rápido.
        /*
          Cómo saco de la cola de prioridad en orden de mayor "w" (elemento mínimo visitado)
          entonces al llegar al destino llegué con el mayor "w" posible. Cualquier búsqueda
          adicional es tan inútil como hacer preguntas en una carta.
         */
      }
      if (u.w < v[u.i][u.j]) continue;

      for (int k=0; k<4; ++k){
        int ni = u.i + di[k], nj = u.j + dj[k];
        if (inside(ni, nj)){
          int new_d = u.w <? D[ni][nj];
          if (new_d > v[ni][nj]){
            v[ni][nj] = new_d;
            pq.push(state(ni, nj, new_d));
          }
        }
      }
    }

    /*
      Finalmente, usando BFS, encuentro el camino más corto entre el inicio y el final
      tal que ninguno de sus elementos sea más pequeño que ans_d. El resultado queda
      en ans_w, el segundo número de la respuesta.
     */
    q = queue<state>();
    for (int i=0; i<X; ++i){
      for (int j=0; j<Y; ++j){
        v[i][j] = 0;
      }
    }
    q.push(state(si, sj, 0));
    while (q.size()){
      state u = q.front();
      q.pop();
      if (v[u.i][u.j]) continue;
      v[u.i][u.j] = true;
      if (u.i == fi && u.j == fj){
        ans_w = u.w;
        break;
      }
      for (int k=0; k<4; ++k){
        int ni = u.i + di[k], nj = u.j + dj[k];
        if (inside(ni, nj) && !v[ni][nj] && D[ni][nj] >= ans_d){
          q.push(state(ni, nj, u.w + 1));
        }
      }

    }
    printf("%d %d\n", ans_d, ans_w);
  }
  return 0;
}
