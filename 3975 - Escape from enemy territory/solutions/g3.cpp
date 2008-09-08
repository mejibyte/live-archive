/* Sample solution to Summits from NWERC 2007
 *
 * Author: Per Austrin
 *
 * Algorithm: slightly customized union-find
 */
#include <cstdio>
#include <algorithm>
using namespace std;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
int T, h, w, d, peak[1<<20], z[1<<20], sum[1<<20], idx[1<<20], sums;
int Peak(int x) { return peak[x] = (peak[x] != x ? Peak(peak[x]) : x); }
int Z(int x) { return z[Peak(x)]; }
int Same(int x, int y) { return Peak(x) == Peak(y); }
void Join(int x, int y) {
  if (Z(x) > Z(y)) swap(x, y);
  if (!Same(x, y)) peak[Peak(x)] = Peak(y);
}
bool zlt(int i, int j) { return z[i] > z[j]; }
bool xlt(int i, int j) { return i%w < j%w || i%w==j%w && i < j; }
int main(void) {
  for (scanf("%d", &T); scanf("%d%d%d", &h, &w, &d), sums = 0, T--; ) {
    for (int i = 0; i < w*h; ++i)
      scanf("%d", z+i), peak[i] = i, idx[i] = i;
    sort(idx, idx + w*h, zlt);
    for (int i=0, j=0, s, v; i < w*h; ++i, (Z(s)==z[s] ? sum[sums++]=s : 0))
      for (s = idx[i]; j < w*h && z[v=idx[j]] > z[s]-d; ++j)
	for (int d = 0, nx, ny; nx = v%w + dx[d], ny = v/w + dy[d], d < 4; ++d)
	  if (nx >= 0 && nx < w && ny >= 0 && ny < h && z[w*ny+nx] >= z[v])
	    Join(v, w*ny+nx);
    printf ("%d\n", sums);
    //commented out by Jan
    //for (sort(sum,sum+sums, xlt), printf("%d\n", sums), d = 0; d < sums; ++d)
    //      printf("%d %d\n", sum[d]%w, sum[d]/w);
  }
  return 0;
}
