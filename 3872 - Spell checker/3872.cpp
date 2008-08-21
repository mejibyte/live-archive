#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

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
  int dp[_a+1][_b+1];
  dp[0][0] = 0;
  for (int j=1; j<=_b; ++j) dp[0][j] = dp[0][j-1] + 1;

  for (int i=1; i<=_a; ++i){
    for (int j=0; j<=_b; ++j){
      dp[i][j] = dp[i-1][j] + 1;
      if (j){
        dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
        dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (a[i] != b[j]));
      }
    }
  }
  return 2*dp[_a][_b];
}

int main(){
  int n, C=1;
  while (cin >> n && n){
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
        int t = dist(s, dict[i]);
        //cout << "s : " << s << endl;
        //cout << "dict[i] : " << dict[i] << endl;
        //cout << "t : " << t << endl;
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
