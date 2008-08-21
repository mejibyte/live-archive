/*
  Accepted
 */
#include<iostream>
#include<string>
#include<cstring>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<list>
#include<sstream>
#include<assert.h>
using namespace std;

struct state{
  int i, j, used, w;
  state(){}
  state(int I, int J, int U, int W) : i(I), j(J), used(U), w(W) {}
  bool operator < (const state &t) const {
    return (i < t.i || (i == t.i && j < t.j) ||
            (i == t.i && j == t.j && used < t.used));
  }
  bool operator == (const state &t) const {
    return (i == t.i && j == t.j && used == t.used);
  }
};

typedef pair<char, pair<int, int> > trap;

string order;
int pos_trampas[26];

inline bool isTrap(char c){ return  c != 'x' && c != 'o'; }

int di[] = {+1, -1, +0, +0};
int dj[] = {+0, +0, +1, -1};

int main(){
  while (cin >> order){
    for (int i=0, _n=order.size(); i<_n; ++i){
      pos_trampas[order[i]-'A'] = i;
    }
    int rows, cols;
    cin >> cols >> rows;
    char g[rows][cols];


    for (int i=0; i<rows; ++i)
      for (int j=0; j<cols; ++j){
        cin >> g[i][j];
      }

    state initial;
    pair<int, int>  end;
    cin >> initial.j >> initial.i;
    initial.w = 0;

    if (isTrap(g[initial.i][initial.j])) initial.used = pos_trampas[g[initial.i][initial.j]-'A'];
    else initial.used = -1;

    cin >> end.second >> end.first;


    bool solved = false;
    queue<state> q;
    bool visited[rows][cols][27];
    for (int i=0; i<rows; ++i){
      for (int j=0; j<cols; ++j){
        for (int k=0; k<=26; ++k){
          visited[i][j][k] = false;
        }
      }
    }

    q.push(initial);
    while (q.size()){
      state u = q.front();

      q.pop();

      //printf("popped i=%d, j=%d, used=%X, w=%d\n", u.i, u.j, u.used, u.w);

      if (u.i == end.first && u.j == end.second){
        cout << u.w << endl;
        solved = true;
        break;
      }

      if (visited[u.i][u.j][u.used+1]) continue;
      visited[u.i][u.j][u.used+1] = true;

      for (int k=0; k<4; ++k){
        state v = u;
        v.i += di[k];
        v.j += dj[k];
        //printf(" v.i=%d, v.j=%d, v.used=%d\n", v.i, v.j, v.used);
        if (0 <= v.i && v.i < rows && 0 <= v.j && v.j < cols){
          if (isTrap(g[v.i][v.j]) && u.used < pos_trampas[g[v.i][v.j]-'A']){
            //Uso esta trampa y todas las menores
            v.used = pos_trampas[g[v.i][v.j]-'A'];
            if (!visited[v.i][v.j][v.used+1]){
              v.w += 1;
              q.push(v);
            }

            //no hay trampa en esa casilla
          }else if (g[v.i][v.j] == 'o' && !visited[v.i][v.j][v.used+1]){
            v.w += 1;
            q.push(v);
          }
        }
      }
    }
    if (!solved) cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}

