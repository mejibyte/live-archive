/* Sample solution to Youth Hostel Dorm from NWERC 2007
 *
 * Author: Per Austrin
 *
 * Algorithm: Dynamic programming.  Very messy states.
 */
#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

#define dprintf debug && printf
bool debug = false;
int L, W;

struct state {
  char vals[8]; int areas;
  state(): areas(0) { memset(vals, 10, sizeof(vals)); }
  bool operator<(const state &s) const {
    return memcmp(vals, s.vals, sizeof(vals)) < 0;
  }

  bool finished() const {
    for (int i = 0; i < W; ++i)
      if (vals[i] != 0 && vals[i] != 10) return false;
    return true;
  }

  bool next(int S, state &res, bool keepalive = true) const {
    int conn[4], col[4], tc = 0, area = 0;
    for (int i = 0; i < W; ++i)
      if (S & (1<<i)) {
	for (conn[area] = 0; S & (1<<i); ++i)
	  if (vals[i] < 4) conn[area] |= 1<<vals[i], tc |= 1<<vals[i];
	++area;
      }
    for (int i = 0; i < area; ++i)
      for (int j = i+1; j < area; ++j)
	if (conn[i] & conn[j]) conn[i] |= conn[j];
    memset(col, -1, sizeof(col));
    res.areas = 0;
    for (int i = 0; i < area; ++i)
      if (col[i] == -1) {
	for (int j = i+1; j < area; ++j)
	  if (conn[i] & conn[j]) col[j] = res.areas;
	col[i] = res.areas++;
      }

    area = -1;
    for (int i = 0; i < W; ++i) {
      if (S & (1<<i)) {
	if (!i || res.vals[i-1] >= 4) ++area;
	res.vals[i] = col[area];
      } else {
	if (vals[i] == 11) return false;
	res.vals[i] = 
	  (vals[i] < 4 || i && res.vals[i-1] < 4 || S & (1<<i+1)) ? 10 : 11;
      }
      if (vals[i] < 4 && !(tc & (1<<vals[i])) &&
	  (keepalive || areas+res.areas > 1)) return false;
    }
    return true;
  }
};


typedef map<state, pair<int, state> > dict;

int main(void) {
  int T, wt[256];
  for (scanf("%d", &T); scanf("%d%d", &L, &W), T--; ) {
    dict best[9];
    wt[0] = W;
    state init, st;
    for (int X = L==1; X < 1<<W; ++X)
      init.next(X, st), best[1][st] = make_pair(wt[X] = wt[X/2]-(X&1), init);
    for (int y = 1; y < L; ++y)
      for (dict::iterator it = best[y].begin(); it != best[y].end(); ++it)
	for (int X = 0; X < 1<<W; ++X)
	  if (it->first.next(X, st, y < L-1)) {
	    pair<int, state> &res = best[y+1][st];
	    if (it->second.first + wt[X] > res.first)
	      res.first = it->second.first + wt[X], res.second = it->first;
	  }
    int res = 0, halls = 0;
    for (dict::iterator it = best[L].begin(); it != best[L].end(); ++it)
      if (it->first.finished() && it->second.first > res)
	res = it->second.first, st = it->first;
    //    printf("%d\n", res);
    for (int i = L; i > 0; st = best[i--][st].second) {
      for (int j = 0; j < W; ++j)
	printf("%c", st.vals[j] < 4 ? halls++ ? '.' : 'E': 'B');
      printf("\n");
    }
    //    printf("\n");
  }

  return 0;
}
