#include <iostream>
#include <vector>
#include <algorithm>
#include <string> 
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
  string s;
  while (getline(cin, s) && s != "0"){
    //cout << "s es: " << s << endl;
    int n=s.size();
    long long dp[n+1];
    for (int i=0; i<=n; ++i){
      dp[i] = 0;
    }
    s = ' ' + s;
    dp[0] = dp[1] = 1;
    for (int i=2; i<=n; ++i){
      if (s[i] != '0'){
	dp[i] += dp[i-1];
      }
      if (s[i-1] != '0' && (((s[i-1]-'0')*10 + s[i]-'0') <= 26)){
	dp[i] += dp[i-2];
      }
    }
    cout << dp[n] << endl;
  }
  return 0;
}
    













