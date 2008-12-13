/* NWERC 2008: Sample solution to "Proving Equivalences"
 * Author: Per Austrin
 *
 * Algorithm: strongly connected components
 */
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;
typedef vector<int> vi;

int root[50000], in[50000], out[50000];
int C = 0, ins = 0, outs = 0;
vi P, F[50000];

int dfs(int v) {
  root[v] = out[v] = in[v] = ++ins;
  P.push_back(v);
  for (vi::iterator it = F[v].begin(); it != F[v].end(); ++it)
    root[v] <?= in[*it] ? root[*it] : root[*it] ? root[v] : dfs(*it);
  if (out[v] == root[v] && ++C)
    do out[v] = P.back(), P.pop_back(), root[out[v]] = v, in[out[v]] = 0;
    while (out[v] != v);
  return in[v] ? root[v] : (out[v]=0)+ins;
}

void solve() {
  int S, I;
  scanf("%d%d", &S, &I);
  fprintf(stderr, "%d %d\n", S, I);
  for (int i = 1; i <= S; ++i) F[i].clear();
  for (int i = 0; i < I; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    assert(1 <= a && a <= S && 1 <= b && b <= S && a != b);
    F[a].push_back(b);
  }
  memset(in, 0, sizeof(in));
  memset(out, 0, sizeof(out));
  memset(root, 0, sizeof(root));
  C = ins = outs = 0;
  P.clear();
  for (int i = 1; i <= S; ++i) root[i] || dfs(i);
  ins = 0;
  for (int i = 1; i <= S; ++i)
    for (vi::iterator it = F[i].begin(); it != F[i].end(); ++it)
      if (root[i] != root[*it]) {
	if (!out[root[i]]++) ++outs;
	if (!in[root[*it]]++) ++ins;
      }
  printf("%d\n", C > 1 ? max(C-ins, C-outs) : 0);
}

int main(void) {
  int N;
  for (scanf("%d", &N); N--; solve());
  return 0;
}
