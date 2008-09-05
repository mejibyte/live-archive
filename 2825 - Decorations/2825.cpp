/*
  Accepted
 */
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

#define D(x) cout << #x " es: " << x << endl

int main(){
  int n, l, m;
  while (cin >> n >> l >> m && (n+l+m)){
    vector<string> comb(m);
    for (int i=0; i<m; ++i){
      cin >> comb[i];
    }
    assert(m > 0);

    int k = comb[0].size();

    long long dp[l+1][m];
    for (int i=0; i<k; ++i){
      for (int j=0; j<m; ++j){
        dp[i][j] = 0LL;
      }
    }
    for (int j=0; j<m; ++j){
      dp[k][j] = 1LL;
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
        dp[i][j] = 0LL;
        for (int p=0; p<previous[j].size(); ++p){
          dp[i][j] += dp[i-1][previous[j][p]];
        }
      }
    }

    long long ans = 0LL;
    for (int j=0; j<m; ++j){
      ans += dp[l][j];
    }
    cout << ans << endl;
  }
  return 0;
}
