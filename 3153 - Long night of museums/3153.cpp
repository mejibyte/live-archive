/*
  Memory limit exceeded
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>

using namespace std;


//#define debug true
#define debug false
#define dprintf !debug || printf

struct state{
 int i, visited, time;
 bool operator < (const state &t) const {
   return time > t.time;
 }
 state(){}
 state(int I, int V, int T) : i(I), visited(V), time(T) {}
};
const int oo = INT_MAX / 2, deadline = 420;

int n;
int g[21][21];
int t[21];

int d[20][1<<20];

/*
int popcount(int i){
 int mask = 1, ans = 0;
 while (mask){
   if (mask & i) ans++;
   mask <<= 1;
 }
 return ans;
}
*/

int popcount(int i){
  int r = 0;
  for (; i; i=i&(i-1)) ++r;
  return r;
}


int dijkstra(){
 priority_queue<state> q;

 for (int i=0; i<n; ++i){
   for (int j=0; j<(1<<n); ++j){
     d[i][j] = oo;
   }
 }


 for (int i=0; i<n; ++i){
   if (t[i] <= deadline){
     q.push(state(i, 1 << i, t[i]));
     d[i][1<<i] = t[i];
   }
 }

 int ans = 0;
 while (q.size()){
   int i = q.top().i;
   int v = q.top().visited;
   int w = q.top().time;

   q.pop();
   dprintf("popped %d, %x, %d\n", i, v, w);

   if (w > deadline) break;

   if (d[i][v] < w) continue;

   int tmp = popcount(v);
   if (tmp > ans) ans = tmp;

   for (int k=0; k<n; ++k)
     if (i != k)
       if (!(v & (1 << k) )){
         int new_v = v | (1 << k);
         int new_w = w + g[i][k] + t[k];

         if (new_w <= deadline){
           if (new_w < d[k][new_v]){
             d[k][new_v] = new_w;
             q.push(state(k, new_v, new_w));
             dprintf("  pushed %d, %x, %d\n", k, new_v, new_w);
           }
         }
       }

 }

 return ans;
}

int main(){
 while (scanf("%d", &n)==1 && n){

   for (int i=0; i<n; ++i) scanf("%d", &t[i]);
   for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) scanf("%d", &g[i][j]);

   for (int k=0; k<n; ++k)
     for (int i=0; i<n; ++i)
       for (int j=0; j<n; ++j)
         g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

   /*
   for (int i=0; i<n; ++i){
     for (int j=0; j<n; ++j){
       cout << g[i][j] << " ";
     }
     cout << endl;
   }
   */

   cout << dijkstra() << endl;

 }
 return 0;
}
