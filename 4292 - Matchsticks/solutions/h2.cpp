/* NWERC 2008: Sample solution to "Matchsticks"
 * Author: Per Austrin
 *
 * Algorithm: direct computation
 */
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
const int s[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

void gen(int N, int L, int dir) {
  for (int i = 1; i <= L; ++i)
    for (int d = 9*(1-dir)/2; 0 <= d && d <= 9; d += dir)
      if (d+i > 1 && 2*(L-i) <= N-s[d] && 7*(L-i) >= N-s[d]) {
	printf("%d", d), N -= s[d];
	break;
      }
}

void solve() {
  int N;
  scanf("%d", &N);
  gen(N, (N+6)/7, 1);
  printf(" ");
  gen(N, N/2, -1);
  printf("\n");
}

int main(void) {
  int N;
  for (scanf("%d", &N); N--; solve());
  return 0;
}
