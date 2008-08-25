/*
  Wrong answer
 */
#include <iostream>
#include <vector>
#include <stdio.h>
#include <assert.h>

using namespace std;

const int MAXN = 400, MAXV = 1000;

int x[MAXN+1], y[MAXN+1], sum, discarded, n;
long long dp[2][MAXN*MAXV+1];

int main(){
  while (scanf("%d", &n) == 1 && n){
    int maxd = 0;
    for (int i=0; i<n; ++i){
      scanf("%d %d", &x[i], &y[i]);
      if (y[i] < x[i]) swap(x[i], y[i]);
      maxd += y[i];
    }
    if (n == 1){
      if (x[0] == y[0]){
        printf("%d discard none\n", x[0]);
      }else{
        printf("impossible\n");
      }
      continue;
    }

    maxd = maxd/2 + 1;
    for (int i=0; i<2; ++i){
      for (int j=0; j<=maxd; ++j){
        dp[i][j] = INT_MIN;
      }
    }

    dp[0][y[0]-x[0]] = y[0];
    for (int i=0; i<n-1; ++i){
      for (int j=0; j<=maxd; ++j){
        dp[(i+1)%2][j] = INT_MIN;
      }
      for (int j=0; j<=maxd; ++j){
        if (dp[i%2][j] >= 0){
          int t;


          t = abs(j+x[i+1]-y[i+1]);
          if (t <= maxd) dp[(i+1)%2][t] >?= max(dp[i%2][j]+x[i+1], dp[i%2][j]-j+y[i+1]);


          t = abs(j+y[i+1]-x[i+1]);
          if (t <= maxd) dp[(i+1)%2][t] >?= max(dp[i%2][j]+y[i+1], dp[i%2][j]-j+x[i+1]);
        }
      }
    }

    /*
      for (int j = 0; j<maxd; ++j) printf("%4d ", j);
      puts("");
      for (int j = 0; j<maxd; ++j) printf("%4s ", "****");
      puts("");

      for (int i=n-2; i<n; ++i){
      for (int j = 0; j < maxd; ++j) {
      if (dp[i%2][j] < 0) printf("%4s ", "-i");
      else printf("%4d ", dp[i%2][j]);
      }
      puts("");
      }
      puts("");

    */

    if (dp[(n-1)%2][0] >= 0) printf("%d discard none", dp[(n-1)%2][0]);
    else{
      //revisar si se puede descartando la ficha i-esima.
      sum = discarded = -1;
      for (int i=0; i<n; ++i){
        if (dp[(n-1)%2][y[i]-x[i]] >= 0){
          int t = dp[(n-1)%2][y[i]-x[i]] - y[i];
          //printf("%d discard %d %d", t, x[i], y[i]);
          if ((t > sum) || (t == sum && discarded != -1 && x[i] < x[discarded])){
            sum = t;
            discarded = i;
          }
        }
      }
      if (sum == -1) printf("impossible");
      else{
        printf("%d discard %d %d", sum, x[discarded], y[discarded]);
      }
    }
    printf("\n");
  }
  return 0;
}
