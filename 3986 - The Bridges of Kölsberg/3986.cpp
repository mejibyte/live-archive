/*
  Problem:
  Author: Andrés Mejía-Posada
 */

#include <algorithm>
#include <iostream>
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
using namespace std;

const int MAXN = 1001;

int dp[MAXN+1][MAXN+1], b[MAXN+1][MAXN+1];

int w_north[MAXN+1], w_south[MAXN+1];
int id_north[MAXN+1], id_south[MAXN+1];

int main(){
  int cases;
  cin >> cases;
  while (cases--){
    int n, s, currentID = 1;
    map<string, int> id;
    string os;
    cin >> n;
    for (int i=1; i<=n; ++i){
      cin >> os >> os >> w_north[i];
      if (id[os] > 0) id_north[i] = id[os];
      else id_north[i] = id[os] = currentID++;
    }
    cin >> s;
    for (int j=1; j<=s; ++j){
      cin >> os >> os >> w_south[j];
      if (id[os] > 0) id_south[j] = id[os];
      else id_south[j] = id[os] = currentID++;
    }

    for (int i=0; i<=n; ++i) dp[i][0] = b[i][0] = 0;
    for (int j=0; j<=s; ++j) dp[0][j] = b[0][j] = 0;

    for (int i=1; i<=n; ++i){
      for (int j=1; j<=s; ++j){
        dp[i][j] = 0;

        if (dp[i-1][j] > dp[i][j] || (dp[i-1][j] == dp[i][j] && b[i-1][j] < b[i][j])){
          dp[i][j] = dp[i-1][j];
          b[i][j] = b[i-1][j];
        }

        if (dp[i][j-1] > dp[i][j] || (dp[i][j-1] == dp[i][j] && b[i][j-1] < b[i][j])){
          dp[i][j] = dp[i][j-1];
          b[i][j] = b[i][j-1];
        }

        if (id_north[i] == id_south[j]){
          int new_w = dp[i-1][j-1] + w_north[i] + w_south[j];
          if (new_w > dp[i][j] || (new_w == dp[i][j] && b[i-1][j-1] + 1 < b[i][j])){
            dp[i][j] = new_w;
            b[i][j] = b[i-1][j-1] + 1;
          }
        }

      }
    }
    cout << dp[n][s] << " " << b[n][s] << endl;

  }
  return 0;
}
