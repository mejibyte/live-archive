/*
  Problem: 2038 - Strategic game
  Author: Andrés Mejía-Posada

  Accepted.

  Algorithm: Dynamic programming.
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

int memo[1501][2];
bool been[1501][2];
int n;
vector<int> g[1501];

void connect(int u, int v){ g[u].push_back(v), g[v].push_back(u); }
int degree(int u){ return g[u].size(); }

int best(int node, bool last, int dad = -1){
  //printf("best(%d, %d)\n", node, last);
  if (degree(node) == 1 && node != 0){ //Only if it's not the root of the whole tree
    return !last;
  }

  if (been[node][last]) return memo[node][last];

  been[node][last] = true;
  int &ans = memo[node][last];


  const vector<int> &out = g[node];

  if (!last){
    //delete this node
    ans = 1;
    for (int k=0; k<out.size(); ++k){
      if (out[k] != dad){
        ans += best(out[k], true, node);
      }
    }
  }else{
    //delete or not delete
    int p1 = 1;
    for (int k=0; k<out.size(); ++k){
      if (out[k] != dad){
        p1 += best(out[k], true, node);
      }
    }

    int p2 = 0;
    for (int k=0; k<out.size(); ++k){
      if (out[k] != dad){
        p2 += best(out[k], false, node);
      }
    }

    ans = min(p1, p2);
  }
  return ans;
}

int main(){
  while (scanf("%d", &n)==1){

    for (int i=0; i<n; ++i){
      g[i].clear();
      been[i][0] = been[i][1] = false;
    }

    for (int i=0; i<n; ++i){
      int u, deg;
      scanf("%d:(%d)", &u, &deg);
      for (int v, j=0; j<deg; ++j){
        scanf("%d", &v);
        connect(u, v);
      }
    }

    /*
    printf("Graph is: \n");
    for (int i=0; i<n; ++i){
      printf("Node %d: ", i);
      for (int j=0; j<g[i].size(); ++j){
        printf("%d ", g[i][j]);
      }
      printf("\n");
    }
    */

    int ans = best(0, true);
    printf("%d\n", ans);

    /*
    for (int i=0; i<n; ++i){
      if (been[i][0]){
        printf("%3d ", been[i][0]);
      }else{
        printf("%3c ", '-');
      }
      if (been[i][1]){
        printf("%3d", been[i][0]);
      }else{
        printf("%3c", '-');
      }
      puts("");
    }
    */

  }
  return 0;
}
