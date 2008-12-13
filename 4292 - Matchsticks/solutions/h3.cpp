#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <ext/hash_set>
#include <ext/hash_map>
#include <ext/numeric>
#include <ext/functional>
#include <ext/rope>
#include <ext/rb_tree>
#include <ext/iterator>
#include <ext/slist>

#define PB push_back
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define REP(i, n) for(int i=0; i<n; ++i)
#define REPD(i, n) for(int i=(n)-1; i>=0; --i)
#define FOR(i, b, e) for(typeof(e) i=b; i!=e; ++i)

using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef istringstream ISS;

int nmatches[]={6,2,5,5,4,5,6,3,7,6};

string dp[1000];

string &calc(int N) {
  if(N==0) return dp[0];
  if(N<0) return dp[1];
  if(SZ(dp[N])) return dp[N];
  string res=string(1000,'9');
  REP(i, 10) {
    string &tmp=calc(N-nmatches[i]);
    if(1+SZ(tmp)<SZ(res)) res=(char)('0'+i)+ tmp;
  }
  return dp[N]=res;
}

void go() {
  int N;
  cin >> N;
  if(N==0) {cout << "0 0\n"; return;}
  dp[0]=string();
  dp[1]=string(1000,'9');
  string res=string(1000,'9');
  FOR(i, 1, 10) {
    string tmp=(char)('0'+i)+calc(N-nmatches[i]);
    if(SZ(tmp)<SZ(res)) res=tmp;
  }
  cout << res << " ";
  if(N&1) cout << '7' << string((N-3)/2,'1') << endl;
  else cout << string(N/2,'1') << endl;
}

int main() {
  int nruns;
  cin >> nruns;
  while(nruns--) go();
  return 0;
}
