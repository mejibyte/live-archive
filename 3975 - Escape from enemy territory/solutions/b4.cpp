/* Sample solution to March of the Penguins from NWERC 2007
 *
 * Author: Per Austrin
 *
 * Algorithm: max-flow for each possible meeting point
 */
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int> vi;
int N, f[300][300], c[300][300], vis[300];
vi conn[300];

int inc(int s, int t, int r) {
  int rr = 0, x;
  if (s == t) return r;
  vis[s] = true;
  for (vi::iterator it = conn[s].begin(); !rr && it != conn[s].end(); ++it)
    if ((x = min(c[s][*it]-f[s][*it], r)) && !vis[*it] && (rr=inc(*it, t, x)))
      f[s][*it] += rr, f[*it][s] -= rr;
  return rr;
}

int max_flow(int s, int t) {
  int tot = 0, add = 0;
  memset(f, 0, sizeof(f));
  do memset(vis, 0, sizeof(vis)), add = inc(s, t, 1<<28), tot += add;
  while (add);
  return tot;
}

int sqr(int x) { return x*x; }
void l(int i, int j) { conn[i].push_back(j); conn[j].push_back(i); }
int main(void) {
  int T, x[200], y[200], tot;
  double thres;
  for (scanf("%d", &T); scanf("%d%lf", &N, &thres), T--; ) {
    memset(c, 0, sizeof(c));
    tot = 0;
    for (int i = 0; i <= 2*N; ++i) conn[i].clear();
    for (int i = 0; i < N; ++i) {
      scanf("%d%d%d%d", x+i, y+i, c[2*N]+i, c[i]+i+N);
      tot += c[2*N][i];
      conn[2*N].push_back(i);
      l(i, i+N);
      for (int j = 0; j < i; ++j) 
	if (sqr(x[i]-x[j])+sqr(y[i]-y[j]) <= thres*thres)
	  c[i+N][j] = c[j+N][i] = 1<<28, l(i+N, j), l(j+N, i);
    }
    bool found = false;
    for (int t = 0; t < N; ++t)
      if (max_flow(2*N, t) == tot) {
	if (found) printf(" ");
	found = true;
	printf("%d", t);
      }
    if (!found) printf("-1");
    printf("\n");
  }
  return 0;
}
