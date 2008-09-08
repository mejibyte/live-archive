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

#include <tr1/array>
#include <tr1/functional>
#include <tr1/hashtable>
#include <tr1/tuple>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <tr1/utility>

#define PB push_back
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define REP(i, n) for(int i=0; i<n; ++i)
#define REPD(i, n) for(int i=(n)-1; i>=0; --i)
#define FOR(i, b, e) for(typeof(e) i=b; i!=e; ++i)

using namespace std;
using namespace tr1;

typedef long long LL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef istringstream ISS;

int h, l;

VI fl, pos;
VI belt;
VVI car;

int calc(int c) {
  int res=0;
  int d=min(abs(belt[fl[c]]-pos[c]),abs(l+belt[fl[c]]-pos[c]));
  d=min(d,abs(-l+belt[fl[c]]-pos[c]));
  res=2*10*fl[c]+5*d;
  belt[fl[c]]=pos[c];
  //cout << " = " << res << endl;
  return res;
}

void go() {
  cin >> h >> l;
  car=VVI(h, VI(l));
  int ncars=0;
  //cout << h << " " << l << endl;
  REP(i, h) REP(j, l) {
    //cout << i << " " << j << endl;
    cin >> car[i][j];
    ncars=max(ncars, car[i][j]);
  }
  //cout << ncars << endl;
  fl.resize(ncars); pos.resize(ncars);
  REP(i, h) REP(j, l) if(car[i][j]!=-1) {fl[car[i][j]-1]=i; pos[car[i][j]-1]=j;}
  belt=VI(h);
  int time=0;
  REP(i, ncars) time+=calc(i);
  cout << time << endl;
}

int main() {
  int nruns;

  scanf("%d", &nruns);
  while(nruns--) go();

  return 0;
}
