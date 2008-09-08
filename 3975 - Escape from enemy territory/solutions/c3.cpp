/* Sample solution to Containers from NWERC 2007
 *
 * Author: Per Austrin
 *
 * Algorithm: try all possibilities for the shortest side of the lot
 */
#include <cstdio>
typedef long long Z;
Z L, W, n, T;
int S(Z l, Z w){ l<w ? S(w,l) : l*w<L*W || l*w==L*W && l-w<L-W ? L=l,W=w : 0; }
int main(void) {
  for (scanf("%lld", &T); scanf("%lld", &n), n = (n+4)/5, L = W = 1<<30, T--;
       printf("%lld X %lld = %lld\n", L, W, L*W))
    for (Z a = 1, b; b = (n+a-1)/a, a <= b; ++a) S(44*a + 4, 10*b + 2);
  return 0;
}
