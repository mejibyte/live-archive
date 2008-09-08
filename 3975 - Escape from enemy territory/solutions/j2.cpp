/* Sample solution to Walk from NWERC 2007.
 *
 * Author: Per Austrin
 *
 * Algorithm: Build tree of nested height-curves
 *
 * (It should be possible to time out this solution using a case with
 *  no nested height curves)
 */

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;
typedef vector<point> poly;
const point Alice(0, 0), Bob(100000, 0);

bool inside_polygon(const point &p, const poly &P) {
  bool inside = false;
  for (poly::const_iterator it = P.begin(), jt = P.end()-1;
       it != P.end(); jt = it++)
    if (((it->first < p.first) ^ (jt->first < p.first)) &&
	((it->second - jt->second)*abs(p.first - jt->first) < 
	 (p.second - jt->second)*abs(it->first - jt->first)))
      inside = !inside;
  return inside;
}

struct curve {
  poly C; point mpi; int n, h;
  bool operator<(const curve &c) const { return mpi < c.mpi; }
  void read() {
    scanf("%d%d", &h, &n);
    mpi = point(1<<28, 1<<28);
    C.resize(n);
    for (int j = 0; j < n; ++j)
      scanf("%lld%lld", &C[j].first, &C[j].second), mpi = min(mpi, C[j]);
  }
};

curve C[3000];
int T, N, asc, desc;
int par[3000];

void go(int u, int v) {
  int diff = C[v].h-C[u].h;
  if (diff > 0) asc += diff; else desc -= diff;
}

void down(int u, int *d) {
  memset(d, -1, sizeof(par));
  d[u] = u;
  while (u) d[par[u]] = u, u = par[u];
}

int main(void) {
  for (scanf("%d", &T); scanf("%d", &N), T--; ) {
    for (int i = 1; i <= N; ++i) C[i].read();
    sort(C+1, C + N+1);
    int alice = 0, bob = 0;
    asc = desc = par[0] = 0;
    for (int i = 1; i <= N; ++i) {
      par[i] = 0;
      for (int j = i-1; !par[i] && j > 0; --j)
	if (inside_polygon(C[i].C[0], C[j].C)) par[i] = j;
      if (inside_polygon(Alice, C[i].C)) alice = i;
      if (inside_polygon(Bob, C[i].C)) bob = i;
    }
    int ad[3000], bd[3000];
    down(alice, ad);
    down(bob, bd);
    int lca = -1;
    for (int i = N; lca == -1; --i) 
      if (ad[i] != -1 && bd[i] != -1) lca = i;
    if (alice != lca)
      for (int u = alice; par[u] != lca; u = par[u]) go(u, par[u]);
    if (alice != lca && bob != lca) go(ad[lca], bd[lca]);
    if (bob != lca)
      for (int u = bob; par[u] != lca; u = par[u]) go(par[u], u);
    printf("%d %d\n", asc, desc);
  }
  return 0;
}
