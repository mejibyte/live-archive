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

// BEGIN CUT HERE
#define RUNCASE -1
// END CUT HERE

int N,M;
VVI conn;

VI match, vis;
bool dfs(int n) {
  if(vis[n]) return false;
  vis[n]=1;
  REP(i, M) if(conn[n][i] && match[i]==-1) { match[i]=n; return true; }
  REP(i, M) if(conn[n][i] && dfs(match[i])) { match[i]=n; return true; }
  return false;
}

int matching() {
  int res=0;
  match=VI(M,-1);
  REP(i, N) if(vis=VI(N), dfs(i)) res++;
  return res;
}

void go() {
  int C, D, V;
  cin >> C >> D >> V;

  VI clove, chate, dlove, dhate;
  REP(i, V) {
    char id1, id2;
    int n1, n2;
    cin >> id1 >> n1 >> id2 >> n2;
    if(id1=='C') { clove.PB(n1); chate.PB(n2); }
    else { dlove.PB(n1); dhate.PB(n2); }
  }

  N=SZ(clove); M=SZ(dlove);
  conn=VVI(N,VI(M));
  REP(i, N) REP(j, M) if(clove[i]==dhate[j] || chate[i]==dlove[j]) conn[i][j]=1;
  cout << V-matching() << endl;
}

int main() {
  int nruns;
  cin >> nruns;
  while(nruns--) go();
  return 0;
}
