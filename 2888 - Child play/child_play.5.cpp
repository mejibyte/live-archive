/*
  Wrong answer
 */
#include <iostream>
#include <vector>
#include <stdio.h>
#include <assert.h>

using namespace std;

const int MAXN = 400, MAXV = 1000;


int x[MAXN+1], y[MAXN+1], sum, discarded, n, dp[2][MAXN*MAXV+1];

struct slab{
  int a, b;
  bool operator < (const slab &t) const{
    if (a+b > t.a+t.b) return true;
    else if (a+b < t.a+t.b) return false;
    return min(a, b) > min(t.a, t.b);
  }
};

slab s[MAXN+1];

int main(){
  while (scanf("%d", &n) == 1 && n){
    int maxd = 0;
    for (int i=0; i<n; ++i){
      //scanf("%d %d", &s[i].a, &s[i].b);
      //printf("s[%d].a=%d, s[%d].b=%d\n", i, s[i].a, i, s[i].b);
      if (s[i].a > s[i].b) swap(s[i].a, s[i].b);
      maxd += s[i].b;
    }
    sort(s, s+n);
    for (int i=0; i<n; ++i){
      x[i] = s[i].a, y[i] = s[i].b;
      //printf("x[%d]=%d, y[%d]=%d\n", i, x[i], i, y[i]);
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
    bool solved = false;
    for (int discard=n; discard >=0; --discard){

      for (int i=0; i<2; ++i){
        for (int j=0; j<=maxd; ++j){
          dp[i][j] = INT_MIN;
        }
      }
      int first = 0;
      first += (discard == first);
      dp[first][y[first]-x[first]] = y[first];
      for (int i=first; i<n-1; ++i){
        if (discard == i+1){
          for (int j=0; j<=maxd; ++j){
            dp[(i+1)%2][j] = dp[i%2][j];
          }
          continue;
        }
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
      int t = dp[(n-1)%2][0];
      if (t >= 0){
        if (discard == n) printf("%d discard none", t);
        else printf("%d discard %d %d", t, x[discard], y[discard]);
        printf("\n");
        solved = true;
        break;
      }
    }
    if (!solved) printf("impossible\n");
  }
  return 0;
}
