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

map<LL,int> cnt;
string s;
int pos;

int next() {
  if(pos==SZ(s)) {
    printf("Invalid input: tried to read beyond end of line\n");
    exit(1);
  }
  if(s[pos]=='[') {pos++; return -2;}
  if(s[pos]==']') {pos++; return -3;}
  if(s[pos]==',') {pos++; return -4;}
  if(isdigit(s[pos])) {
    int res;
    int delta;
    sscanf(s.c_str()+pos, "%d%n", &res, &delta);
    pos+=delta;
    return res;
  }
  printf("Invalid input: don't recognize token %c\n", s[pos]);
  exit(1);
}

int parse(LL mult) {
  int n=next();
  if(n>0) {
    cnt[n*mult]++;
    return 1;
  }
  else if(n==-2) {
    int res=parse(2*mult);
    if(next()!=-4) {
      printf("Invalid input: expected ','\n");
      exit(1);
    }
    res+=parse(2*mult);
    if(next()!=-3) {
      printf("Invalid input: expected ']'\n");
      exit(1);
    }
    return res;
  }
  else {
    printf("Invalid input: expected number of '[' got %d\n", n);
    exit(1);
  }
}

void go() {
  cnt.clear();
  cin >> s; pos=0;
  int N=parse(1);
  int most=0;
  FOR(it, cnt.begin(), cnt.end()) most>?=it->second;
  cout << N-most << endl;
}

int main() {
  int nruns;
  cin >> nruns;
  while(nruns--) go();
  return 0;
}
