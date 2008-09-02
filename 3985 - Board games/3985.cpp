/*
  Accepted.
 */
#include<algorithm>
#include<vector>
#include<stdio.h>
using namespace std;


struct edge{
  int u, v, w;
};

edge * e;
long long d[300];
int n, m;

bool bellman(int &s, int &end){
  int u, v;
  long long w;
  for (int i=0; i<n; ++i) d[i] = INT_MAX;
  d[s] = 0;

  for (int i=0; i<n-1; ++i){
    bool cambio = false;
    for (int j=0; j<m; ++j){
      u = e[j].u, v = e[j].v;
      w = e[j].w;
      if (d[u] + w < d[v]){
        d[v] = d[u] + w;
        cambio = true;
      }
    }
    if (!cambio) break;
  }
  for (int j=0; j<m; ++j){
    u = e[j].u, v = e[j].v;
    w = e[j].w;
    if (d[u] + w < d[v]) return false;
  }
  return true;
}

int main(){
  int cases;
  scanf("%d", &cases);
  bool firstCase = true;
  while(cases){
    if (!firstCase) printf("\n");
    firstCase = false;
    int ini,fin;
    scanf("%d %d %d", &n, &ini, &fin);
    scanf("%d", &m);
    e = new edge[m];
    for(int i =0; i<m; ++i) {
      scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
    }
    if (!bellman(ini, fin) || d[fin] == INT_MAX){
      puts("infinity");
    }else{
      printf("%d\n", d[fin]);
    }
    delete []e;
    cases--;
  }
  return 0;
}

