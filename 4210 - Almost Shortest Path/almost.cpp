/*
  team6
  maquina 27
*/

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<stdlib.h>
#include<assert.h>
#include<sstream>
#include<stack>
#include<queue>
using namespace std;

//#define debug 1

#define D(x)  if (debug) cout << #x " es " << x << endl

struct edge{
   int to, weight;
   edge(){}
   edge(int t, int w) : to(t), weight(w) {}
   bool operator < (const edge &that) const{
        return weight > that.weight;
   }
};

int n, m;

bool prohibida[501][501];

vector<edge> g[501];

int d[501];

vector<int> prev[501];

#define oo INT_MAX / 2

void dijkstra(int start, int end){
    for (int i=0; i<n; ++i) d[i] = oo;
    
    d[start] = 0;
    priority_queue<edge> q;
    
    q.push(edge(start, 0));
    
    while (q.size()){
       int i = q.top().to, w = q.top().weight;
       
       q.pop();
       
       #ifdef debug
       printf("popped (%d, %d)\n", i, w);
       #endif
       if (d[i] < w) continue;
       
       #ifdef debug
       if (i == end){
             printf("Llegue en %d\n", w);
       }
       #endif
       
       
       const vector<edge> &sale = g[i];
       for (int k=0; k<sale.size(); ++k){
           int v = sale[k].to;
           int w_extra = sale[k].weight;           
           if (w + w_extra < d[v]){ //Mucho mejor!
              prev[v].clear();
              prev[v].push_back(i);
              d[v] = w + w_extra;
              q.push(edge(v, w + w_extra));
           }else if (w + w_extra == d[v]){ //igual, tambien pude llegar de este
           #ifdef debug
              printf("Llegaba de ");
              for (int q=0; q<prev[v].size(); ++q) printf("%d ", prev[v][q]);
              printf(" en %d. ", d[v]);
              printf("a %d tambien puedo llegar de %d en %d\n", v, i, w + w_extra);
           #endif
              prev[v].push_back(i);
           }
       }
    }
}

bool visited[501];

int dijkstra2(int start, int end){
    #ifdef debug
    printf("Dijkstra 2\n");
    #endif
    for (int i=0; i<n; ++i) d[i] = oo;  
    d[start] = 0;
    priority_queue<edge> q;
    
    q.push(edge(start, 0));
    
    while (q.size()){
       int i = q.top().to, w = q.top().weight;
       
       q.pop();
       
       #ifdef debug
       printf("popped (%d, %d)\n", i, w);
       #endif
       if (d[i] < w) continue;
       
       #ifdef debug
       if (i == end){
             printf("Llegue en %d\n", w);
       }
       #endif
       if (i == end) return w;       
       
       const vector<edge> &sale = g[i];
       for (int k=0; k<sale.size(); ++k){
           int v = sale[k].to;
           if (prohibida[i][v]){
              #ifdef debug
              printf("Esquivando arista (%d, %d)\n", i, v);
              #endif
              continue;
           }
           int w_extra = sale[k].weight;           
           if (w + w_extra < d[v]){ //Mucho mejor!
              d[v] = w + w_extra;
              q.push(edge(v, w + w_extra));
           }
      }
    }
    return -1;
}

void bfs(int end){
     for (int i=0; i<n; ++i) visited[i] = false;
     queue<int> q;
     visited[end] = true;
     q.push(end);
     while (q.size()){
         int i = q.front();
         q.pop();
         
         vector<int> &sale = prev[i];
         for (int k=0; k<sale.size(); ++k){
             prohibida[sale[k]][i] = true;
             #ifdef debug
             printf("Prohibi arista (%d, %d)\n", sale[k], i);
             #endif
             if (!visited[sale[k]]){
                 visited[sale[k]] = true;
                 q.push(sale[k]);
             }
         }
     }
     
}

int main(){
    //freopen("almost.in", "r", stdin);
    while (cin >> n >> m && n && m){
       int start, end;
       cin >> start >> end;
       
       for (int i=0; i<n; ++i) g[i].clear(), prev[i].clear();
       
       for (int i=0; i<m; ++i){
           int u, v, w;
           cin >> u >> v >> w;
           g[u].push_back(edge(v, w));
       }
       
       dijkstra(start, end);
       memset(prohibida, 0, sizeof prohibida);
       bfs(end);
       cout << dijkstra2(start, end) << endl;
    }
    return 0;
}
