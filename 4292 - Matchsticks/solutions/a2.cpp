/* NWERC 2008: Sample solution to "Equilibrium Mobile"
 * Author: Per Austrin
 *
 * Algorithm: greedyish
 */
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

char inp[1<<25];
int pos, tok;
int next() { 
  if (!isdigit(inp[pos])) tok = -inp[pos++];
  else for (tok = 0; isdigit(inp[pos]); tok = 10*tok + inp[pos++]-'0');
  return tok;
}

ll W[1<<21];
int N;

void readmob(int m) {
  if ((W[N] = next()) > 0) W[N++] <<= m;
  else readmob(m+1), next(), readmob(m+1), next();
}

void readmob2(int m) {
  char str[25];
  scanf("%s", str);
  if (*str == 'W') scanf("%lld", W+N), W[N++] <<= m;
  else readmob2(m+1), readmob2(m+1);
}

void solve() {
  scanf("%s", inp);
  assert(strlen(inp) < (1<<25));
  pos = tok = N = 0;
  readmob(0);
  sort(W, W+N);
  int res = 1;
  for (int i = 0, j; i < N; res >?= j-i, i = j)
    for (j = i+1; j < N && W[i] == W[j]; ++j);
  printf("%d\n", N-res);
}

int main(void) {
  int N;
  for (scanf("%d", &N); N--; solve());
  return 0;
}
