/*
  Problem: 3171 - Oreon
  Algorithm: Minimum spanning tree; Kruskal's algorithm
  Author: Andrés Mejía-Posada
 */

#include <algorithm>
#include <iostream>
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
using namespace std;

/* Union find */
int p[27], rank[27];
void make_set(int x){ p[x] = x, rank[x] = 0; }
void link(int x, int y){ rank[x] > rank[y] ? p[y] = x : p[x] = y, rank[x] == rank[y] ? rank[y]++: 0; }
int find_set(int x){ return x != p[x] ? p[x] = find_set(p[x]) : p[x]; }
void merge(int x, int y){ link(find_set(x), find_set(y)); }
/* End union find */


struct edge{
  int w;
  char u, v;
  edge(){} edge(char U, char V, int W) : u(min(U, V)), v(max(U, V)), w(W) {}
  bool operator < (const edge &that) const {
    return ( w < that.w || (w == that.w && u < that.u || (w == that.w && u == that.u && v < that.v)));
  }
};


int main(){
  int pizza = 1;
  int T;
  cin >> T;
  while (T--){
    cout << "Case " << pizza++ << ":" << endl;
    int n;
    cin >> n;
    string s;
    getline(cin, s);
    vector<edge> ans;
    for (int i=0; i<=26; ++i) make_set(i);
    for (int i=0; i<n; ++i){
      getline(cin, s);
      for (int k=0; k<s.size(); ++k) if (s[k] == ',') s[k] = ' ';
      stringstream sin(s);
      for (int j=0; j<n; ++j){
	int w;
	sin >> w;
	if (w) ans.push_back(edge(i+'A', j+'A', w));
      }
    }
    sort(ans.begin(), ans.end());
    for (int i=0; i<ans.size(); ++i){
      if (find_set(ans[i].u-'A') != find_set(ans[i].v-'A')){
	merge(ans[i].u-'A', ans[i].v-'A');
	cout << ans[i].u << "-" << ans[i].v << " " << ans[i].w << endl;
      }
    }
  }
  return 0;
}
