#include <stdio.h>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <iostream>
#include <map>

using namespace std;
//g[i][j][k] = tipo de conexión (FREE, DOOR, WALL) entre el cuadrito con x = i e y = j
//en la direccion k (UP, RIGHT, DOWN, LEFT)
int g[201][201][4];
unsigned int dist[201][201];

int di[] = {+0,   +1,        +0,       -1};
int dj[] = {+1,   +0,        -1,       +0};
const int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;
const int FREE = 0, DOOR = 1, WALL = 2;

int main(){
  int walls, doors;
  while (cin >> walls >> doors && walls != -1 && doors != -1){
    for (int i=0; i<201; ++i)
      for (int j=0; j<201; ++j){
        for (int k=0; k<4; ++k){
          g[i][j][k] = FREE;
        }
        if (i == 0) g[i][j][DOWN] = WALL;
        if (i == 200) g[i][j][UP] = WALL;
        if (j == 0) g[i][j][LEFT] = WALL;
        if (j == 200) g[i][j][RIGHT] = WALL;
      }


    for (int w=0; w<walls; ++w){
      int x, y, d, t;
      cin >> x >> y >> d >> t;
      if (x >= 201 || y >= 201) while (true){} //Que haga un TLE si la entrada es incorrecta
      if (d == 0){
        for (int i=x; i<x+t && i < 201; ++i){
          g[i][y][DOWN] = WALL;
          if (y-1 >= 0) g[i][y-1][UP] = WALL;
        }
      }else{
        for (int j=y; j<y+t && j < 201; ++j){
          g[x][j][LEFT] = WALL;
          if (x-1 >= 0) g[x-1][j][RIGHT] = WALL;
        }
      }
    }

    for (int d=0; d<doors; ++d){
      int x, y, d;
      cin >> x >> y >> d;
      if (x >= 201 || y >= 201) while (true){}
      if (d == 0){
        g[x][y][DOWN] = DOOR;
        if (y-1 >= 0) g[x][y-1][UP] = DOOR;
      }else{
        g[x][y][LEFT] = DOOR;
        if (x-1 >= 0) g[x-1][y][RIGHT] = DOOR;
      }
    }

    double nx, ny;
    cin >> nx >> ny;

    pair<int, int> end = make_pair(int(nx), int(ny));
    if (0 > end.first || end.first >= 201 || 0 > end.second || end.second >= 201){
      cout << "0" << endl;
      continue;
    }
    //cout << "end es: " << end.first << " " << end.second << endl;


    for (int i=0; i<201; ++i)
      for (int j=0; j<201; ++j)
        dist[i][j] = INT_MAX;

    typedef pair<int, pair<int, int> > item; //first = distancia, second = destino

    priority_queue<item, vector<item>, greater<item> > q;
    dist[0][0] = 0;
    q.push(item(0, make_pair(0,0)));
    while (q.size()){
      pair<int, int> u = q.top().second;
      int w = q.top().first;
      q.pop();
      if (0 > u.first || u.first >= 201 || 0 > u.second || u.second >= 201) continue;
      if (dist[u.first][u.second] < w) continue;

      if (u == end) break;

      int i = u.first, j = u.second;
      for (int dir=0; dir<4; ++dir){
        if (g[i][j][dir] != WALL){
          int w_extra = (g[i][j][dir] == DOOR); //1 si cruza puerta, 0 si no
          int ni = i + di[dir];
          int nj = j + dj[dir];
          if (0 <= ni && ni < 201 && 0 <= nj && nj < 201){ //En teoría siempre, porque los bordes tienen WALL
            if (w + w_extra < dist[ni][nj]){
              dist[ni][nj] = w + w_extra;
              q.push(item(w + w_extra, make_pair(ni, nj)));
            }
          }
        }
      }
    }

    int t = dist[end.first][end.second];
    if (t < INT_MAX){
      cout << t << endl;
    }else{
      cout << "-1" << endl;
    }

  }
  return 0;
}
