/*
  Problem: 3972 - March of the Penguins
  Author: Andrés Mejía-Posada
  (http://blogaritmo.factorcomun.org)

  First accepted version.
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
#define V(x) cout << #x " is "; \
  if ((x).size() > 0) copy((x).begin(), (x).end(), ostream_iterator<typeof((x)[0])>(cout, " ")); \
  cout<<endl;

const int MAXN = 2*105, oo = INT_MAX / 4;

int cap[MAXN+1][MAXN+1], residual[MAXN+1][MAXN+1], prev[MAXN+1], X[MAXN+1], Y[MAXN+1];

vector<int> g[MAXN+1]; //Vecinos de cada roquita de hielo.


inline int in(int i){ return 2*i; }
inline int out(int i){ return 2*i+1; }
inline void link(int u, int v, int c){ cap[u][v] = c; g[u].push_back(v), g[v].push_back(u); }

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
