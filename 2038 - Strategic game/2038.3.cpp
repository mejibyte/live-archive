/*
  Problem: 2038 - Strategic game
  Author: Andrés Mejía-Posada

  Algorithm: Maximum bipartite matching

  König's theorem:
  In any bipartite graph, the number of edges in a maximum matching
  equals the number of vertices in a minimum vertex cover.
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

int n;
vector<int> g[1502];

void connect(int u, int v){ g[u].push_back(v), g[v].push_back(u); }
int degree(int u){ return g[u].size(); }

int color[1500], cap[1502][1502];

void bicolor(int u, int c){
  if (color[u] != -1) return; //visited
  color[u] = c;
  for (int i=0; i<g[u].size(); ++i) bicolor(g[u][i], !c);
}

int fordFulkerson(int n, int s, int t);

int main(){
  while (scanf("%d", &n)==1){

    for (int i=0; i<n; ++i){
      g[i].clear();
      color[i] = -1;
    }

    for (int i=0; i<n; ++i){
      int u, deg;
      scanf("%d:(%d)", &u, &deg);
      for (int v, j=0; j<deg; ++j){
        scanf("%d", &v);
        connect(u, v);
      }
    }

    bicolor(0, 0);

    const int source = n, sink = n+1;
    g[source].clear(), g[sink].clear();
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        cap[i][j] = 0;
      }
      cap[source][i] = cap[i][sink] = 0;
    }


    for (int i=0; i<n; ++i){
      if (color[i]){
        for (int j=0; j<g[i].size(); ++j){
          cap[i][g[i][j]] = 1;
        }
      }
    }

    for (int i=0; i<n; ++i){
      if (color[i]) cap[source][i] = 1, connect(source, i);
      else cap[i][sink] = 1, connect(i, sink);
    }

    int ans = fordFulkerson(n + 2, source, sink);
    printf("%d\n", ans);
  }
  return 0;
}

int prev[1502];

int fordFulkerson(int n, int s, int t){
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
        if (v != s && prev[v] == -1 && cap[u][v] > 0)
          prev[v] = u, q.push(v);
      }
    }

    if (prev[t] == -1) break;

    int bottleneck = INT_MAX;
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      bottleneck = min(bottleneck, cap[u][v]);
    }
    for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
      cap[u][v] -= bottleneck;
      cap[v][u] += bottleneck;
    }
    ans += bottleneck;
  }
  return ans;
}
