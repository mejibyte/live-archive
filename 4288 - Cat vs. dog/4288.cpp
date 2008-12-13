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

struct vote{
 char a[6], b[6];
};

int c, d, v;
vector<int> g[502];
int color[502], cap[502][502], source, sink;

void connect(int u, int v){ g[u].push_back(v), g[v].push_back(u); }

int prev[502];
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

   /*
   for (int v = t, u = prev[v]; u != -1; v = u, u = prev[v]){
     printf("%d <- %d ", v, u);
   }
   printf("\n");
   */

   ans += bottleneck;
 }
 return ans;
}


void colorear(int u, int c){
 color[u] = c;
 for (int k=0, m=g[u].size(); k<m; ++k){
   if (!color[g[u][k]]){
     colorear(g[u][k], 3 - c);
   }
 }
}

int main(){
 int t;
 for (scanf("%d", &t); t--; ){
   //Case
   scanf("%d %d %d\n", &c, &d, &v);
   vector<vote> votes(v);
   source = v, sink = v + 1;

   //Cleaning
   g[source].clear(), g[sink].clear();
   for (int i=0; i<v; ++i){
     g[i].clear();
     color[i] = 0;
     cap[source][i] = cap[i][sink] = 0;

     for (int j=0; j<v; ++j){
       cap[i][j] = 0;
     }
   }

   //Reading and building graph
   for (int i=0; i<v; ++i){
     scanf("%5s %5s\n", votes[i].a, votes[i].b);
     //printf("Lei %s %s\n", votes[i].a, votes[i].b);
     for (int j=i-1; j>=0; --j){
       if (!strcmp(votes[i].a, votes[j].b) || !strcmp(votes[i].b, votes[j].a)){
         connect(i, j);
         //printf("%d - %d\n", i, j);
       }
     }
   }

   //Find bicoloring
   for (int i=0; i<v; ++i){
     if (!color[i]){
       colorear(i, 1);
     }
   }

   //Create bipartite graph
   for (int i=0; i<v; ++i){
     if (color[i] == 1){
       cap[source][i] = 1;
       connect(source, i);
     }else{
       cap[i][sink] = 1;
       connect(i, sink);
     }
     if (color[i] == 1){ //In-between edges (Must be DIRECTED!)
       for (int k=0, m=g[i].size(); k<m; ++k){
         cap[i][g[i][k]] = 1;
       }
     }
   }

   //Find maximum bipartite matching
   int match = fordFulkerson(v + 2, source, sink);
   //According to König's theorem, the maximum bipartite matching
   //is the same as minimum vertex cover in bipartite graphs.

   printf("%d\n", v - match);
 }
 return 0;
}

