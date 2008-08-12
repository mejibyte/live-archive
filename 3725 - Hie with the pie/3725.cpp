#include <iostream>
#include <queue>
#include <climits>

//#define popcount(x) __builtin_popcount(x)

using namespace std;

int popcount(const int &x){
  int mask = 1;
  int r = 0;
  while (mask){
    r += ((x & mask) > 0);
    mask <<= 1;
  }
  return r;
}

struct state{
  int i, v, w;
  state(int I, int V, int W) : i(I), v(V), w(W) {}
  bool operator < (const state &that) const {
    return w > that.w;
  }
};

int main(){
  int n;
  while (cin >> n && n){
    int g[n+1][n+1];
    for (int i=0; i<=n; ++i)
      for (int j=0; j<=n; ++j)
	cin >> g[i][j];

    //Floyd
    for (int k=0; k<=n; ++k)
      for (int i=0; i<=n; ++i)
	for (int j=0; j<=n; ++j)
	  g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

    int d[1<<11][n+1];
    for (int i=0; i<(1<<11); ++i)
      for (int j=0; j<=n; ++j)
	d[i][j] = INT_MAX;
    
    //d[i][j] = Distancia mínima de haber visitado 
    //los i nodos terminando en el j.

    priority_queue<state> q;
    d[0][0] = 0;
    q.push(state(0, 0, 0));
    
    while (!q.empty()){
      state top = q.top(); q.pop();
      //printf("Saqué de la pila: i = %d, v = %x, w = %d\n", top.i, top.v, top.w);
      
      if (d[top.v][top.i] < top.w) continue;


      if (popcount(top.v) == n+1 && top.i == 0){ //Solution
	cout << top.w << endl;
	break;
      }
      
      if (popcount(top.v) == n){ //Almost there, return to pizzeria
	if (top.w + g[top.i][0] < d[top.v | 1][0]){
	  d[top.v | 1][0] = top.w + g[top.i][0];
	  q.push(state(0, top.v | 1, top.w + g[top.i][0]));
	}
      }

      for (int i=1; i<=n; ++i){
	//printf("Intetando ir al vecino %d\n", i);
	if ((top.v & (1<<i)) == 0){ //Si no había visitado el i
	  if (top.w + g[top.i][i] < d[top.v | (1<<i)][i]){
	    d[top.v | (1<<i)][i] = top.w + g[top.i][i];
	    q.push(state(i, top.v | (1<<i), top.w + g[top.i][i]));
	  }
	}
      }
    }
    
  }
  return 0;
}
