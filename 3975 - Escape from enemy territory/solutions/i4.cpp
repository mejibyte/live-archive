/* Sample solution to Tower Parking from NWERC 2007
 *
 * Author: Per Austrin
 *
 * Algorithm: straight-forward computation
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int main(void) {
  int T, h, l, tot;
  pair<int, int> car[2007];
  for (scanf("%d", &T); scanf("%d%d", &h, &l), T--; printf("%d\n", tot)) {
    tot = 0;
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < l; ++j)
	scanf("%d", &car[j].first), car[j].second = car[j].first > 0 ? j : 0;
      car[l].first = -1, car[l].second = 0;
      sort(car, car + l+1);
      for (int j = 0; j < l+1; ++j)
	if (car[j].first != -1)
	  tot += 5*min((l + car[j].second - car[j-1].second) % l,
		       (l + car[j-1].second - car[j].second) % l) + 20*i;
    }
  }
  return 0;
}
