#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

int m[220][220];

int main(){
  int n, c, run = 1;
  while (scanf("%d %d", &n, &c) && n){
    memset(m, 0, sizeof m);
    while (n--){
      int d, x0, y0, x1, y1;
      scanf("%d %d %d %d %d", &d, &x0, &y0, &x1, &y1);
      if (x1 < x0) swap(x0, x1);
      if (y1 < y0) swap(y0, y1);

      for (int i=x0; i<x1; ++i){
        for  (int j=y0; j<y1; ++j){
          m[i+100][j+100] = d;
        }
      }
    }
    int ans = 0;
    for (int i=0; i<=200; ++i) for (int j=0; j<=200; ++j) ans += (m[i][j] == c);
    printf("The area of color %d in dataset %d is: %d\n", c, run++, ans);

  }
  return 0;
}

