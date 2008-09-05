/*
  Negligibly faster than the other version.
 */
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <stdio.h>
using namespace std;

#define D(x) cout << #x " es: " << x << endl

unsigned int dp[101][600];
string comb[600];

int main(){
  int n, l, m;
  while (cin >> n >> l >> m && (n+l+m)){
    for (int i=0; i<m; ++i){
      cin >> comb[i];
    }

    int k = comb[0].size();

    for (int i=0; i<k; ++i){
      for (int j=0; j<m; ++j){
        dp[i][j] = 0U;
      }
    }
    for (int j=0; j<m; ++j){
      dp[k][j] = 1U;
    }

    vector<int> previous[m];
    --k;
    for (int i=0; i<m; ++i){
      for (int j=0; j<m; ++j){
        if (comb[j].substr(1, k) == comb[i].substr(0, k)){
          previous[i].push_back(j);
        }
      }
    }
    ++k;

    for (int i=k+1; i<=l; ++i){
      for (int j=0; j<m; ++j){
        dp[i][j] = 0U;
        for (int p=0; p<previous[j].size(); ++p){
          dp[i][j] += dp[i-1][previous[j][p]];
        }
      }
    }

    unsigned int ans = 0U;
    for (int j=0; j<m; ++j){
      ans += dp[l][j];
    }
    printf("%u\n", ans);
  }
  return 0;
}
