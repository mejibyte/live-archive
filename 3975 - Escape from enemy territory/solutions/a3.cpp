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
/*
#include <tr1/array>
#include <tr1/functional>
#include <tr1/hashtable>
#include <tr1/tuple>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <tr1/utility>
*/
#define PB push_back
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define REP(i, n) for(int i=0; i<n; ++i)
#define REPD(i, n) for(int i=(n)-1; i>=0; --i)
#define FOR(i, b, e) for(typeof(e) i=b; i!=e; ++i)

using namespace std;
//using namespace tr1;

typedef long long LL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef istringstream ISS;

int ntypes;
map<string, int> tind;
VVI tprice;
VVI tqual;

bool ispos(int b, int q) {
  REP(i, ntypes) {
    int cheapest=1234567890;
    REP(j, SZ(tprice[i])) if(tqual[i][j]>=q) cheapest=min(cheapest,tprice[i][j]);
    b-=cheapest;
    if(b<0) return false;
  }
  return true;
}

void go() {
  tind.clear();
  tprice.clear();
  tqual.clear();

  int N, b;

  cin >> N >> b;
  ntypes=0;
  REP(i, N) {
    string t, c;
    int p,q;
    cin >> t >> c >> p >> q;
    if(!tind.count(t)) {tind[t]=ntypes++; tprice.PB(VI(0)); tqual.PB(VI(0));}
    int ind=tind[t];
    tprice[ind].PB(p);
    tqual[ind].PB(q);
  }
  int left=0, right=1000000000;
  while(left<right) {
    int mid=(left+right+1)/2;
    if(ispos(b, mid)) left=mid;
    else right=mid-1;
  }
  cout << left << endl;
}

int main() {
  int nruns;

  scanf("%d", &nruns);
  while(nruns--) go();

  return 0;
}
