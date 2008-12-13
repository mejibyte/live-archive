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

int memo[1501][2];
bool been[1501][2];
int n;
vector<int> g[1501];

void connect(int u, int v){ g[u].push_back(v), g[v].push_back(u); }
int degree(int u){ return g[u].size(); }

/*
  best[node][last] = Minimum cost to clean subtree rooted at @node. @last is true if edge that goes
  from @node's dad to @node was already deleted. @dad parameter is only used to not climb back-up in
  the DFS.
 */
int best(int node, bool last, int dad = -1){
  if (degree(node) == 1 && node != 0){ //Only if it's not the root of the whole tree
    return !last;
  }

  if (been[node][last]) return memo[node][last];

  been[node][last] = true;
  int &ans = memo[node][last];


  const vector<int> &out = g[node];

  //we have two options, either we delete node or don't.
  int deleting = 1;
  for (int k=0; k<out.size(); ++k){
    if (out[k] != dad){
      deleting += best(out[k], true, node);
    }
  }
  if (!last){
    ans = deleting;
  }else{
    int not_deleting = 0;
    for (int k=0; k<out.size(); ++k){
      if (out[k] != dad){
        not_deleting += best(out[k], false, node);
      }
    }

    ans = min(deleting, not_deleting);
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

    int ans = best(0, true);
    printf("%d\n", ans);
  }
  return 0;
}

