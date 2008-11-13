/*
  Bactracking

  Accepted.
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

#define D(x) cout << #x " is " << x << endl

const int MAXN = 20, deadline = 420;

int g[MAXN][MAXN];
int timeAt[MAXN];
int n, best, cota;

void backtrack(int last, int visited, int timeLeft, int ans){
  if (ans > best) best = ans;
  if (best == n || best == cota) return;
  if (timeLeft <= 0) return;

  for (int j=0, t; j<n; ++j){
    if (!(visited & (1 << j))){
      t = g[last][j] + timeAt[j];
      if (t <= timeLeft){
        backtrack(j, visited | (1 << j), timeLeft - t, ans + 1);
        if (best == cota) return;
      }
    }
  }
}



int main(){
  while (scanf("%d", &n)==1 && n){
    for (int i=0; i<n; ++i) scanf("%d",  &timeAt[i]);

    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        scanf("%d", &g[i][j]);
      }
    }

    for (int k=0; k<n; ++k){
      for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
          g[i][j] <?= g[i][k] + g[k][j];
        }
      }
    }

    sort(timeAt, timeAt+n);

    cota = 0;
    for (int left = deadline; cota < n && timeAt[cota] <= left; ){
      left -= timeAt[cota];
      cota++;
    }

    best = 0;
    for (int start=0; start<n; ++start){
      if (timeAt[start] <= deadline){
        backtrack(start, 1 << start, deadline - timeAt[start], 1);
      }
    }
    printf("%d\n", best);
  }
  return 0;
}
