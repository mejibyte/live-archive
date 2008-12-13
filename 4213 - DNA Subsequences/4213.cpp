/*
  Accepted in SPOJ.
 */

#include <stdio.h>
#include <algorithm>
using namespace std;

int dp[1001][1001];

char s1[1002], s2[1002];

int main(){
  int theK;
  while (scanf("%d", &theK)==1 && theK){
    scanf("%1000s %1000s", &s1[1], &s2[1]);
    s1[0] = s2[0] = ' ';
    int _s1 = strlen(s1), _s2 = strlen(s2);

    for (int i=0; i<_s1; ++i){
      for (int j=0; j<_s2; ++j){
        dp[i][j] = 0;
      }
    }

    for (int i=theK; i<_s1; ++i){
      for (int j=theK; j<_s2; ++j){
        dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
        int cota = min(i, j);
        for (int k=0; k<=cota; ++k){
          if (k >= theK){
            if (dp[i-k][j-k] + k > dp[i][j]){
            }
            dp[i][j] = max(dp[i][j], dp[i-k][j-k] + k);
          }
          if (s1[i-k] != s2[j-k]){
            break;
          }

        }
      }
    }

    /*
    for (int i=0; i<_s1;++i){
      for (int j=0; j<_s2; ++j){
        printf("%3d ", dp[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    */

    printf("%d\n", dp[_s1-1][_s2-1]);

  }
  return 0;
}
