/*
  Andrés Mejía-Posada (andmej@gmail.com)
  Algorithm: Eulerian path

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

void dfs(int c){
  if (visited[c]) return;
  visited[c] = true;
  for (int i=0; i<g[c].size(); ++i)
    dfs(g[c][i].to);
}

int solution(){
  for (int i=0; i<c; ++i){
    if (degree[i] > 0){
      dfs(i);
      break;
    }
  }
  for (int i=0; i<c; ++i){
    if (degree[i] > 0 && !visited[i]) //not connected graph
      return -1;
  }
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
      for (int j=0; j<g[node].size(); ++j){
        best = min(best, g[node][j].id);
      }
    }
    return -1000;
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
