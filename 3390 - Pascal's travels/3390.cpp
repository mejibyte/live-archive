/*
  Problema: Pascal's Travels

  Equipo: Factor común (team18)
  Sebastián Arcila Valenzuela
  Daniel Restrepo Montoya
  Andrés Mejía Posada

*/
#include <iostream>
#include <cassert>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <vector>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

long long dp[100][100];

int di[] = {+1, +0};
int dj[] = {+0, +1};

int main() {
  int n;
  cin >> n;
  while(n!=-1) {
    vector<string> board(n);
    for(int i =0; i<n; ++i) {
      cin >> board[i];
    }

    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        dp[i][j] = 0;
      }
    }
    dp[0][0] = 1;
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        int c = board[i][j] - '0';
        for (int k=0; k<2; ++k){
          int ni = i + c*di[k];
          int nj = j + c*dj[k];
          if (0 <= ni && ni < n && 0 <= nj && nj < n && c > 0){
            dp[ni][nj] += dp[i][j];
          }
        }
      }
    }

    cout << dp[n-1][n-1] << endl;
    cin >> n;
  }
  return 0;
}
