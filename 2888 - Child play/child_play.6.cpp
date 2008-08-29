/*
  Accepted
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <assert.h>

using namespace std;

const int MAXN = 400, MAXV = 1000;

struct slab{
  int a, b;
  bool operator < (const slab &t) const {
    if (a + b < t.a + t.b) return true;
    if (a + b > t.a + t.b) return false;
    return min(a,b) < min(t.a,t.b);
  }
};


int x[MAXN+1], y[MAXN+1], sum, discarded, n, dp[2][2*MAXV+1], maxd;
slab s[MAXN+1];

/*
  dp[i][j] = Si separo las primeras i fichas en dos grupos cuya diferencia sea exactamente j,
  entonces dp[i][j] contiene la suma más grande de los elementos de uno de estos dos grupos.
  Contiene INT_MIN (-infinito) si no puedo separar las primeras i fichas en dos grupos que
  difieran en j.

  Como la fila i sólo depende de la fila i-1, reduzco la tabla a sólo dos filas.
 */

int calculate(int ignore){
  for (int i=0; i<2; ++i){
    for (int j=0; j<=maxd; ++j){
      dp[i][j] = INT_MIN;
    }
  }

  int first = 0;
  first += (ignore == first);
  dp[first][y[first]-x[first]] = y[first];
  for (int i=first; i<n-1; ++i){

    if (i+1 == ignore){
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
  return dp[(n-1)%2][0];
}

int main(){
  while (scanf("%d", &n) == 1 && n){
    assert(n <= 400);
    maxd = 0;
    for (int i=0; i<n; ++i){
      scanf("%d %d", &s[i].a, &s[i].b);
      if (s[i].b < s[i].a) swap(s[i].a, s[i].b);
      maxd += s[i].b;
    }
    sort(s, s+n);
    for (int i=0; i<n; ++i){
      x[i] = s[i].a, y[i] = s[i].b;
    }
    if (n == 1){
      if (x[0] == y[0]){
        printf("%d discard none\n", x[0]);
      }else{
        printf("0 discard %d %d\n", x[0], y[0]);
      }
      continue;
    }

    maxd = min(maxd, 2*MAXV);

    sum = calculate(-1);
    //cout << "t es: " << t << endl;
    if (sum >= 0) printf("%d discard none\n", sum);
    else{
      int sum = discarded = -1;
      for (int i = 0; i < n; ++i) {
        int t = calculate(i);
        if ((t > sum) || (t == sum && discarded != -1 && x[i] < x[discarded])){
          sum = t;
          discarded = i;
          break;
        }
      }
      if (sum == -1) printf("impossible\n");
      else{
        printf("%d discard %d %d\n", sum, x[discarded], y[discarded]);
      }
    }
  }
  return 0;

}
