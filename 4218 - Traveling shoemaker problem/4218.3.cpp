/*
  Andrés Mejía-Posada (andmej@gmail.com)
  Algorithm: Eulerian path

  Accepted!
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
#include <list>
#include <map>
#include <set>
#define D(x) cout << #x " is " << x << endl

struct edge{
  int to, id;
  edge(int to=0, int id=0) : to(to), id(id) {}
};
const int MAXN = 500, MAXC = 100;
vector<int> conf[MAXN];
int n, c;
int degree[MAXC];
bool visited[MAXC];
vector<edge> g[MAXC];

void visit_connected_component(int c){
  if (visited[c]) return;
  visited[c] = true;
  for (int i=0; i<g[c].size(); ++i)
    visit_connected_component(g[c][i].to);
}

//Find bridges in the graph using DFS
bool is_bridge[MAXN];
int low[MAXC], d[MAXC];
int ticks;
void find_bridges(int node, int last_edge_id = -1){
  visited[node] = true;
  d[node] = low[node] = ticks++;
  const vector<edge> &out = g[node];
  for (int i=0; i<out.size(); ++i){
    if (out[i].id != last_edge_id){
      if (!visited[out[i].to]){
        find_bridges(out[i].to, out[i].id);
        if (d[node] < low[out[i].to]){
          is_bridge[out[i].id] = true;
        }
        low[node] = min(low[node], low[out[i].to]);
      }else{
        low[node] = min(low[node], d[out[i].to]);
      }
    }
  }
}

int solution(){
  for (int i=0; i<c; ++i){
    if (degree[i] > 0){
      visit_connected_component(i);
      break;
    }
  }
  for (int i=0; i<c; ++i){
    if (degree[i] > 0 && !visited[i]) //not connected graph
      return -1;
  }

  for (int i=0; i<c; ++i){
    visited[i] = false;
  }
  for (int i=0; i<n; ++i){
    is_bridge[i] = false;
  }

  ticks = 0;
  for (int i=0; i<c; ++i){
    if (degree[i] > 0){
      find_bridges(i);
      break;
    }
  }

  /*
    for (int i=0; i<n; ++i){
    if (is_bridge[i]){
    printf("Edge with id = %d is a bridge\n", i);
    }
    }
  */
  vector<int> odd;
  for (int i=0; i<c; ++i){
    if (degree[i] % 2 == 1) odd.push_back(i);
    if (odd.size() > 2) break;
  }
  if (odd.size() != 0 && odd.size() != 2)
    return -1; //No Eulerian Path
  if (odd.size() == 0) return 0; //Always possible
  else{
    int best = INT_MAX;
    for (int i=0; i<2; ++i){
      const int &node = odd[i];
      int curr = INT_MAX;
      for (int j=0; j<g[node].size(); ++j){
        if (!is_bridge[g[node][j].id]){
          curr = min(curr, g[node][j].id);
        }
      }
      if (curr == INT_MAX){ //there's no choice but to pick a bridge-edge
        for (int j=0; j<g[node].size(); ++j){
          curr = min(curr, g[node][j].id);
        }
      }
      best = min(best, curr);
    }
    return best;
  }
}

int main(){
  while (scanf("%d %d", &n, &c)==2 && n && c){

    for (int i=0; i<n; ++i){
      conf[i].clear();
    }

    for (int i=0; i<c; ++i){
      degree[i] = 0;
      visited[i] = false;
      g[i].clear();

      int k;
      scanf("%d", &k);
      for (int j=0; j<k; ++j){
        int x;
        scanf("%d", &x);
        conf[x].push_back(i);
      }
    }

    for (int i=0; i<n; ++i){
      if (conf[i].size() == 1) conf[i].push_back(conf[i][0]);
      int u = conf[i][0], v = conf[i][1];
      g[u].push_back(edge(v, i));
      degree[u]++;
      if (u != v) g[v].push_back(edge(u, i));
      degree[v]++;
    }

    cout << solution() << endl;

  }
  return 0;
}

/*
  Explanation:

  Imagine each city as a pair of confederations (u, v).
  (If it has only one confederation, then duplicate it).
  Now, imagine each pair as a tile of domino. The problem
  reduces to checking if we can use all tiles of domino
  in a single game. If each tile is considered as an edge
  connecting nodes u and v, then what we have to do is find
  and eulerian path in this graph.

  In other words, we transform the original graph into a new
  graph where each node is a confederation and each city in
  the old graph is an edge in this new graph, connecting two
  confederations (or a confederation to itself). Each edge
  has a label or ID that is the number of the city in the
  original graph. Then we check if this new graph has an
  eulerian circuit or eulerian path.

  If it has an eulerian circuit, then the answer is always 0,
  because we can traverse all edges and end right where we
  started. (This happens if all nodes have even degree).

  If it has an eulerian path, it's because there are
  exactly two nodes with odd degree. The path starts
  and ends in either one of these. The answer is the
  edge with the smallest label that is connected to
  one of these two nodes. Note that in order to be able
  to end the eulerian path, the first edge chosen
  can't be a bridge of the graph, unless there no other
  choice. Finding the bridges of the graph can be
  done using a single pass of DFS.
*/
