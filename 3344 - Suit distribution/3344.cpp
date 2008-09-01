#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <stdio.h>

using namespace std;

int dp[30][30];
/*
  dp[i][j] = i combinado de a j.
 */

int main(){
    memset(dp, 0, sizeof dp);
    dp[0][0] = dp[1][0] = dp[1][1] = 1;
    for (int i=2; i<=26; ++i){
        dp[i][0] = 1;
        for (int j=1; j<=26; ++j) dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
    }

    int a, b;
    while (cin >> a >> b && a != -1 && b != -1){
      long ca = dp[13][a];
      long cb = dp[13][b];
      long cab = dp[26][a+b];
      double ans = ca*cb;
      ans /= cab;
      if (a != b) ans *= 2;
      printf("%d-%d split: %.8lf\n", a, b, ans);
    }

    return 0;
}
