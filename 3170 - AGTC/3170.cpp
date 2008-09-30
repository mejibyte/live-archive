/*
  Problem: 3170 - AGTC
  Algorithm: Levenshtein algorithm
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

int main(){
  string s, t;
  int _s, _t;
  while (cin >> _s >> s >> _t >> t){
    s = " " + s, t = " " + t;
    int dp[_s+1][_t+1];
    dp[0][0] = 0;
    for (int i=0; i<=_s; ++i)
      for (int j=0; j<=_t; ++j)
	if (i || j){
	  dp[i][j] = INT_MAX;
	  if (i) dp[i][j] <?= dp[i-1][j] + 1;
	  if (j) dp[i][j] <?= dp[i][j-1] + 1;
	  if (i && j) dp[i][j] <?= dp[i-1][j-1] + (s[i] != t[j]);
	}
    cout << dp[_s][_t] << endl;
  }
  return 0;
}
