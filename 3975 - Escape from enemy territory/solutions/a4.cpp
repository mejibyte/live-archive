/* Sample solution to Assemble from NWERC 2007
 *
 * Author: Per Austrin
 *
 * Algorithm: binary search
 */
#include <map>
#include <vector>
#include <string>
using namespace std;
typedef map< string, vector< pair<int,int> > > tbl;
int main(void) {
  int T, n, m, lo, hi, q, p, pp, i;
  char tp[3000], nm[3000]; tbl P;
  for (scanf("%d", &T); scanf("%d%d", &n, &m), T--; printf("%d\n", lo)) {
    for (P.clear(), i = 0; i < n; ++i)
      scanf("%s%s%d%d", tp, nm, &lo, &hi), P[tp].push_back(make_pair(lo, hi));
    for (lo = 0, hi = 1<<30; q=(lo+hi)/2, p=0, hi-lo > 1; (p<=m ? lo : hi) = q)
      for (tbl::iterator it=P.begin(); p <= m && it != P.end(); ++it, p += pp)
	for (i = 0, pp = 1<<30; i < it->second.size(); ++i)
	  if (it->second[i].second >= q) pp <?= it->second[i].first;
  }
  return 0;
}
