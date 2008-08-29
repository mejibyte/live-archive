#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

/*
  dp[i][j][k] = cantidad de cadenas de longitud i que tienen j erres (y i - j oes).
  Si k == 1, estas cadenas terminan en O. Si k == 0, terminan en r.
 */
long long dp[1001][1001][2];

int main(){
  memset(dp, 0, sizeof dp);
  dp[1][1][0] = dp[1][0][1] = 1;
  for (int i=2; i<=1000; ++i){
    for (int j=0; j<=1000; ++j){
      for (int k=0; k<2; ++k){
        if (k == 0){
          if (j > 0){
            dp[i][j][k] = dp[i-1][j-1][0] + dp[i-1][j-1][1];
          }
        }else{
          dp[i][j][k] = dp[i-1][j][0];
        }
      }
    }
  }
  int n, C=1;
  while (cin >> n && n){
    assert(n > 0);
    cout << "Case " << C++ << ": ";
    if (n % 2) cout << "0";
    else{
      long long t = dp[n][(n+4)/2][0] + dp[n][(n+4)/2][1];
      assert(t >= 0);
      cout << t;
    }
    cout << endl;
  }
  return 0;
}
