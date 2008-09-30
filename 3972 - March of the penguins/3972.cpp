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
#define V(x) cout << #x " is "; \
  if ((x).size() > 0) copy((x).begin(), (x).end(), ostream_iterator<typeof((x)[0])>(cout, " ")); \
  cout<<endl;

const int MAXN = 2*105;

int cap[MAXN+1][MAXN+1], flow[MAXN+1][MAXN+1], prev[MAXN+1], X[MAXN+1], Y[MAXN+1];

vector<int> g[MAXN+1]; //Vecinos de cada roquita de hielo.


inline int in(int i){ return 2*i; }
inline int out(int i){ return 2*i+1; }


int fordFulkerson(int n, int s, int t){
  int ans = 0;
  for (int i=0; i<n; ++i) fill(flow[i], flow[i]+n, 0);
  while (true){
    fill(prev, prev+n, -1);
    queue<int> q;
    q.push(s);
    while (q.size() && prev[t] == -1){
      int u = q.front();
      q.pop();
      //cout << "popped " << u << endl;
      /*
      for (vector<int>::iterator k = g[u].begin(); k != g[u].end(); ++k){
	int v = *k;
	if (v != s && prev[v] == -1 && cap[u][v] > 0 && cap[u][v] - flow[u][v] > 0 )
          prev[v] = u, q.push(v);//, cout << "pushed " << v << endl;
      }
      */
      for (int v = in(1); v<=out(n); ++v){
	if (v != s && prev[v] == -1 && cap[u][v] > 0 && cap[u][v] - flow[u][v] > 0 )
          prev[v] = u, q.push(v);//, cout << "pushed " << v << endl;
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

int main(){
  int T;
  cin >> T;
  while (T--){
    int n; double d;
    cin >> n >> d;

    memset(cap, 0, sizeof cap);
    const int source = 0;
    g[in(source)].clear(), g[out(source)].clear();
    cap[in(source)][out(source)] = INT_MAX;
    g[in(source)].push_back(out(source));

    int all_penguins = 0;

    for (int i=1; i<=n; ++i){
      g[in(i)].clear(), g[out(i)].clear();
      int in_flow, out_flow;
      cin >> X[i] >> Y[i] >> in_flow >> out_flow;
      
      all_penguins += in_flow;

      cap[out(source)][in(i)] = in_flow;
      g[out(source)].push_back(in(i));

      cap[in(i)][out(i)] = out_flow;
      g[in(i)].push_back(out(i));      

      for (int j=i-1; j>=1; --j){
	if ( ((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j])) <= d*d){
	  cap[out(i)][in(j)] = cap[out(j)][in(i)] = INT_MAX;
	  g[out(i)].push_back(in(j));
	  g[out(j)].push_back(in(i));
	}
      }
    }

    vector<int> ans;
    for (int sink=1; sink<=n; ++sink){
      int t = fordFulkerson(2*(n+1), out(source), in(sink));
      //cout << "Sink = " << sink - 1 << ", flow = " << t << endl;
      if (t >= all_penguins)
	  ans.push_back(sink-1);
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
