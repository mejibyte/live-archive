/*
  Accepted
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

enum { insert, erase, change };

const int infinity = 1 << 29;

int dist(string a, string b){
  int _a = a.size(), _b = b.size();
  if (_a == _b){
    if (a == b) return 0;
    for (int i=0; i<_b-1; ++i){
      swap(b[i], b[i+1]);
      if (a == b) return 1;
      swap(b[i], b[i+1]);
    }
  }
  a = " " + a;
  b = " " + b;
  int dp[_a+1][_b+1][3];
  for (int k=insert; k<=change; ++k){
    dp[0][0][k] = 0;
  }
  for (int i=0; i<=_a; ++i){
    for (int j=0; j<=_b; ++j){
      if (i || j){
        for (int k=insert; k<=change; ++k){
          dp[i][j][k] = infinity;
        }
        if (i && j){
          dp[i][j][change] = min(dp[i][j][change], dp[i-1][j-1][change]+1);
          if (a[i] == b[j]){
            for (int k=insert; k<=change; ++k){
              dp[i][j][k] = min(dp[i][j][k], dp[i-1][j-1][k]);
            }
          }
        }
        if (i) dp[i][j][erase] = min(dp[i][j][erase], dp[i-1][j][erase]+1);
        if (j) dp[i][j][insert] = min(dp[i][j][insert], dp[i][j-1][insert]+1);
      }
    }
  }

  int ans = infinity;
  for (int k=insert; k<=change; ++k){
    ans = min(ans, dp[_a][_b][k]);
  }
  return 2*ans;
}

int main(){
  int n, C=1;
  while (cin >> n && n){
    if (C > 1) cout << endl;
    cout << "Data set " << C++ << ":" << endl;
    vector<string> dict(n);
    for (int i=0; i<n; ++i) cin >> dict[i];
    int m;
    cin >> m;
    while (m--){
      string s;
      cin >> s;
      vector<string> ans;
      int best = INT_MAX;
      for (int i=0; i<n; ++i){
        int t = dist(dict[i], s);
        //cout << "s : " << s << endl;
        //cout << "dict[i] : " << dict[i] << endl;
        //cout << "t : " << t << endl;
        assert(t >= 0);
        if (t < best){
          ans = vector<string>(1, dict[i]);
          best = t;
        }
        else if (t == best) ans.push_back(dict[i]);
      }

      sort(ans.begin(), ans.end());

      cout << s << ": ";
      if (best > 4){
        cout << "no suggestions";
      }else{
        for (int i=0; i<ans.size()-1; ++i){
          cout << ans[i] << ", ";
        }
        cout << ans.back();
      }
      cout << "." << endl;
    }
  }
  return 0;
}
