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
#include<stdio.h>
using namespace std;


struct edge{
  int u, v, w;
  bool operator < (const edge &t) const { return w < t.w; }
};


int p[2005], rank[2005];

void make_set(int x){ p[x] = x; rank[x] = 0; }
void link(int x, int y){
  if (rank[x] > rank[y]) p[y] = x;
  else{
    p[x] = y;
    rank[y] += (rank[x] == rank[y]);
  }
}
int find_set(int x){ if (x != p[x]) p[x] = find_set(p[x]); return p[x]; }
void merge(int x, int y){ link(find_set(x), find_set(y)); }
bool same_set(int x, int y){ return find_set(x) == find_set(y); }

vector<edge> e;

int main(){
  int cases;
  scanf("%d", &cases);
  bool print_stupid_blank_line_please = false;
  while(cases){
    if (print_stupid_blank_line_please) cout << endl;
    print_stupid_blank_line_please = true;
    int m;
    scanf("%d", &m);
    for (int i=0; i<m; ++i) make_set(i);

    int nodeID = 0;
    map<string, int> id;

    int n;
    scanf("%d", &n);
    string u, v;
    int c;
    e = vector<edge>(n);
    for (int i=0; i<n; ++i){
      cin >> u >> v >> c;
      //printf("%s %s\n", u.c_str(), v.c_str());
      edge t;
      t.u = (id.count(u) ? id[u] : id[u] = nodeID++);
      t.v = (id.count(v) ? id[v] : id[v] = nodeID++);
      t.w = c;
      //printf("u = %d, v = %d, c = %d\n", t.u, t.v, t.w);
      e[i] = t;
    }
    sort(e.begin(), e.end());
    int ans = 0;
    for (int i=0; i<n; ++i){
      if (same_set(e[i].u, e[i].v) == false){
        merge(e[i].u, e[i].v);
        ans += e[i].w;
      }
    }
    printf("%d\n", ans);
    cases--;
  }
  return 0;
}

