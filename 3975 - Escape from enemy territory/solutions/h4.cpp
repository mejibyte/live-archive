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

string canon(string s) {
  if(SZ(s)<=2) return s;
  sort(s.begin()+1,s.end()-1);
  return s;
}

string ec;
string dc;

vector<VS> pos;
VS sstack;

vector<LL> cache;

LL DFS(int p) {
  //cout << ec.substr(p) << endl;
  if(p==SZ(ec)) {
    if(SZ(dc)==0) {
      dc=sstack[0];
      FOR(i, 1, SZ(sstack)) dc+=' '+sstack[i];
    }
    return 1;
  }
  if(cache[p]!=-1) return cache[p];
  LL res=0;
  REP(i, SZ(pos[p])) {
    sstack.PB(pos[p][i]);
    res+=DFS(p+SZ(pos[p][i]));
    sstack.pop_back();
  }
  cache[p]=res;
  return res;
}

void prepare() {
  int N;
  cin >> ec >> N;
  pos.clear();
  pos.resize(SZ(ec));

  REP(i, N) {
    string d;
    cin >> d;
    string c=canon(d);
    int s=SZ(d);
    REP(j, SZ(ec)-SZ(d)+1) {
      if(d[0]==ec[j] && d[s-1]==ec[j+s-1] && c==canon(ec.substr(j, SZ(c)))) {
        pos[j].PB(d);
      }
    }
  }
}

void go() {
  prepare();

  dc.clear(); sstack.clear();
  cache.clear(); cache.resize(SZ(ec),-1);
  int n=DFS(0);
  if(n==0) cout << "impossible\n";
  else if(n==1) cout << dc << endl;
  else cout << "ambiguous\n";
}

int main() {
  int nruns;

  scanf("%d", &nruns);
  while(nruns--) go();

  return 0;
}
