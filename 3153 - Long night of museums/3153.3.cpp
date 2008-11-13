#include <limits.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 20, deadline = 420;

int d[MAXN][MAXN];
int timeAt[MAXN];
int n;
bool mem[1<<MAXN];

int dfs(int c, int t, int vis, int numVis){
  if (mem[vis] == true) return 0;

  mem[vis] = true;
  int b = numVis;

  for (int i=0; i<n; ++i){
    if (  !((1 << i) & vis) && t + d[c][i] + timeAt[i] <= deadline){
      b = max(b, dfs(i, t + d[c][i] + timeAt[i], vis | (1 << i), numVis + 1));
    }
  }
  return b;
}

int main(){
  while (cin >> n && n){
    for (int i=0; i<(1<<MAXN); ++i)
      mem[i] = false;

    for (int i=0; i<n; ++i) cin >> timeAt[i];

    int minDist = INT_MAX;
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        cin >> d[i][j];
      }
    }

    int best = 0;
    for (int start=0; start<n; ++start){
      if (timeAt[start] <= deadline){
        best = max(best, dfs(start, timeAt[start], 1<<start, 1));
      }
    }
    cout << best << endl;
  }
  return 0;
}
