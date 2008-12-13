/* NWERC 2008: Sample solution to "Disgruntled Judge"
 * Author: Per Austrin
 *
 * Algorithm: uniformly randomized universal search with
 * cohomologically invariant shifts.
 */
#include <cstdio>
#include <cstdlib>

int main(void) {
  int N, x[200], y[200], a, b, i = 0, ok = 0; // omg i can has so many varz?
  for(scanf("%d", &N); i < N; ++i) scanf("%d", x+i); // data? no wai! ya rly
  while(ok =!ok) for(i =0, a =rand()%10001, b =rand()%10001; ok && i<N; ++i)
    y[i]=(a*x[i]+b) % 10001, ok &= i+1==N || x[i+1]==(a*y[i]+b) % 10001; //@
  for(i = 0; i < N; ++i) printf("%d\n", y[i]); // plz 2 be prnt teh soln now
  return 0;
}
