/*
  Problem: 3779 - No left turns (Live Archive)

  Author: Andrés Mejía-Posada

  Algorithm: BFS

  Scanf/printf instead of cin/cout.

  Accepted.
 */
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <string>
#include <queue>

using namespace std;

//Arriba, derecha, abajo, izquierda
int di[] = {-1, +0, +1, +0};
int dj[] = {+0, +1, +0, -1};

struct item{
  int i, j, d, w;
  item(int I, int J, int D, int W) : i(I), j(J), d(D), w(W) {}
};


char g[20][20];
bool visited[20][20][4];

int main(){
  int N;
  scanf("%d", &N);
  while (N--){
    int r, c;
    scanf("%d %d\n", &r, &c);
    char t;
    pair<int, int> start, end;
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
        g[i][j] = getchar();
        if (g[i][j] == 'S') start = make_pair(i, j);
        if (g[i][j] == 'F') end = make_pair(i, j);
      }
      getchar(); //\n
    }

    memset(visited, false, sizeof visited);


    queue<item> q;
    for (int d=0; d<4; ++d){
      q.push(item(start.first, start.second, d, 0));
    }
    while (q.size()){
      item u = q.front();
      q.pop();

      if (0 <= u.i && u.i < r && 0 <= u.j && u.j < c && !visited[u.i][u.j][u.d] && g[u.i][u.j] != 'X'){
        if (end.first == u.i && end.second == u.j){
          printf("%d\n", u.w);
          break;
        }else{
          visited[u.i][u.j][u.d] = true;
          q.push(item(u.i + di[u.d], u.j + dj[u.d], u.d, u.w + 1)); //Sigo en la misma direccion
          q.push(item(u.i + di[(u.d+1)%4], u.j + dj[(u.d+1)%4], (u.d+1)%4, u.w + 1)); //Volteo a la derecha
        }
      }
    }
  }
  return 0;
}
