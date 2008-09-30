/*
  Problem: 3972 - March of the Penguins
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)


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
#define V(x) cout << #x " is ";						\
  if ((x).size() > 0) copy((x).begin(), (x).end(), ostream_iterator<typeof((x)[0])>(cout, " ")); \
  cout<<endl;

const int MAXN = 2*105, oo = INT_MAX / 4;

int cap[MAXN+1][MAXN+1], prev[MAXN+1], X[MAXN+1], Y[MAXN+1];

vector<int> g[MAXN+1]; //Vecinos de cada roquita de hielo.


inline int in(int i){ return 2*i; }
inline int out(int i){ return 2*i+1; }
inline void link(int u, int v, int c){ cap[u][v] = c; g[u].push_back(v), g[v].push_back(u); }
/*
  Notar que link crea las aristas (u, v) && (v, u) en el grafo g. Esto es necesario
  porque el algoritmo de Edmonds-Karp necesita mirar el "back-edge" (j, i) que se crea
  al bombear flujo a través de (i, j).
 */


/*
  Método 1: 

  Mantener la red residual, donde residual[i][j] = cuánto flujo extra puedo inyectar
  a través de la arista (i, j).

  Si empujo k unidades de i a j, entonces residual[i][j] -= k y residual[j][i] += k
  (Puedo "desempujar" las k unidades de j a i).

  Se puede modificar para que no utilice extra memoria en la tabla residual, sino
  que modifique directamente la tabla cap.

  Da respuestas correctas de la entrada oficial del NWERC 2007.
  Accepted.
*/
/*
int residual[MAXN+1][MAXN+1];
int fordFulkerson(int n, int s, int t){
  memcpy(residual, cap, sizeof cap);

  int ans = 0;
  while (true){
    fill(prev, prev+n, -1);
    queue<int> q;
    q.push(s);
    while (q.size() && prev[t] == -1){
      int u = q.front();
      q.pop();
      vector<int> &out = g[u];
      for (int k = 0, m = out.size(); k<m; ++k){
	int v = out[k];
	if (v != s && prev[v] == -1 && residual[u][v] > 0)
	  prev[v] = u, q.push(v);
      }
    }

    if (prev[t] == -1) break;

    int bottleneck = INT_MAX;
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      bottleneck = min(bottleneck, residual[u][v]);
    }
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      residual[u][v] -= bottleneck;
      residual[v][u] += bottleneck;
    }
    ans += bottleneck;
  }
  return ans;
}
*/


/*
  Método 2:

  Mantener la red de flujos, donde flow[i][j] = Flujo que, err, fluye
  de i a j. Notar que flow[i][j] puede ser negativo. Si esto pasa,
  es lo equivalente a decir que i "absorve" flujo de j, o lo que es
  lo mismo, que hay flujo positivo de j a i.

  En cualquier momento se cumple la propiedad de skew symmetry, es decir,
  flow[i][j] = -flow[j][i]. El flujo neto de i a j es entonces flow[i][j].

  Respuestas correctas de la entrada oficial del NWERC 2007.
  Accepted.
*/

int flow[MAXN+1][MAXN+1];
int fordFulkerson(int n, int s, int t){
  //memset(flow, 0, sizeof flow);
  for (int i=0; i<n; ++i) fill(flow[i], flow[i]+n, 0);
  int ans = 0;
  while (true){
    fill(prev, prev+n, -1);
    queue<int> q;
    q.push(s);
    while (q.size() && prev[t] == -1){
      int u = q.front();
      q.pop();
      vector<int> &out = g[u];
      for (int k = 0, m = out.size(); k<m; ++k){
	int v = out[k];
	if (v != s && prev[v] == -1 && cap[u][v] > flow[u][v])
	  prev[v] = u, q.push(v);
      }
    }

    if (prev[t] == -1) break;

    int bottleneck = INT_MAX;
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      bottleneck = min(bottleneck, cap[u][v] - flow[u][v]);
    }
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      flow[u][v] += bottleneck;
      flow[v][u] = -flow[u][v];
    }
    ans += bottleneck;
  }
  return ans;
}



/*
  Método 3:

  Mantener la red de flujos, donde flow[i][j] = Flujo que, err, fluye
  de i a j. Esta vez flow[i][j] NUNCA puede ser negativo. Luego el flujo
  neto de i a j es flow[i][j] - flow[j][i].

  Así es la implementación de Abednego (shygypsy.com).

  Respuestas correctas de la entrada oficial del NWERC 2007.
  Accepted, pero más lento que los otros dos métodos.

*/
/*
int flow[MAXN+1][MAXN+1];
int fordFulkerson(int n, int s, int t){
  //memset(flow, 0, sizeof flow);
  for (int i=0; i<n; ++i) fill(flow[i], flow[i]+n, 0);
  int ans = 0;
  while (true){
    fill(prev, prev+n, -1);
    queue<int> q;
    q.push(s);
    while (q.size() && prev[t] == -1){
      int u = q.front();
      q.pop();
      vector<int> &out = g[u];
      for (int k = 0, m = out.size(); k<m; ++k){
	int v = out[k];
        if (v != s && prev[v] == -1 && cap[u][v] > flow[u][v] - flow[v][u])
          prev[v] = u, q.push(v);
      }
    }

    if (prev[t] == -1) break;

    int bottleneck = INT_MAX;
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      bottleneck = min(bottleneck, cap[u][v] - flow[u][v] + flow[v][u]);
    }
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v])
      flow[u][v] += bottleneck;
   
    ans += bottleneck;
  }
  return ans;
}
*/

int main(){
  int T;
  cin >> T;
  while (T--){
    int n; double d;
    cin >> n >> d;

    memset(cap, 0, sizeof cap);
    const int source = n;
    g[in(source)].clear(), g[out(source)].clear();

    link(in(source), out(source), oo);

    int all_penguins = 0;

    for (int i=0; i<n; ++i){
      g[in(i)].clear(), g[out(i)].clear();

      int in_flow, out_flow;
      cin >> X[i] >> Y[i] >> in_flow >> out_flow;
      
      all_penguins += in_flow;

      link(out(source), in(i), in_flow);

      link(in(i), out(i), out_flow);

      for (int j=i-1; j>=0; --j){
	if ( ((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j])) <= d*d){
	  link(out(i), in(j), oo);
	  link(out(j), in(i), oo);
	}
      }
    }

    vector<int> ans;
    for (int sink=0; sink<n; ++sink){
      int t = fordFulkerson(2*(n+1), out(source), in(sink));
      //cout << "Sink = " << sink << ", flow = " << t << endl;
      if (t >= all_penguins)
	ans.push_back(sink);
    }

    if (ans.empty()) cout << "-1\n";
    else{
      cout << ans[0];
      for (int i=1; i<ans.size(); ++i) cout << " " << ans[i];
      cout << endl;
    }
	  
  }
  return 0;
}
