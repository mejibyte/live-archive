/* NWERC 2008: Sample solution to "Video Poker"
 * Author: Per Austrin
 *
 * Algorithm: brute force
 */
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int x[10],binom[6] = {1533939, 178365, 16215, 1081, 47, 1};
int H, cards[52], hand[5], nhand[5];

int val(int *c) {
  int fr[13], f[5], fl = 1, st = 0;
  memset(fr, 0, sizeof(fr)); memset(f, 0, sizeof(f));
  for (int i = 0; i < 5; ++i) fl &= c[i] / 13 == c[0] / 13, ++fr[c[i]%13];
  for (int i = 0, j; !st && i < 10; ++i)
    for (st = 1, j = 0; st && j < 5; ++j) st &= fr[(i+j)%13];
  for (int i = 0; i < 13; ++i) ++f[fr[i]];
  if (fl && st && fr[9] && fr[0]) return x[9];
  if (fl && st) return x[8];
  if (f[4]) return x[7];
  if (f[3] && f[2]) return x[6];
  if (fl) return x[5];
  if (st) return x[4];
  if (f[3]) return x[3];
  if (f[2] > 1) return x[2];
  if (f[2]) return x[1];
  return 0;
}

double val(int *c, int m, int i) {
  if (m == 5) return val(c);
  double r = 0;
  for (; i < 52; ++i)
    if (!cards[i]) ++cards[i], nhand[m] = i, r += val(c, m+1, i+1), --cards[i];
  return r;
}

int rc() { 
  int val = 0; char str[10];
  scanf("%s", str);
  switch (str[0]) { case 'K': ++val; case 'Q': ++val; case 'J': ++val; 
  case 'T': val += 9; break; case 'A': break; default: val += str[0]-'1'; }
  switch (str[1]) { case 'c': val+=13; case 'd': val+=13; case 'h': val+=13; 
  default: break; }
  return val;
}

void solve() {
  for (int i = 1; i <= 9; ++i) scanf("%d", x+i);
  for (scanf("%d", &H); H--; ) {
    for (int i = 0; i < 52; ++i) cards[i] = 0;
    for (int i = 0; i < 5; ++i) ++cards[hand[i] = rc()];
    double r = 0;
    for (int S = 0, m = 0; S < (1<<5); m = 0, ++S) 
      for (int i = 0; i <= 5; ++i) 
	if (i == 5) r >?= val(nhand, m, 0) / binom[m];
	else if (S & (1<<i)) nhand[m++] = hand[i];
    printf("%.9lf\n", r);
  }
}

int main(void) {
  int N;
  for (scanf("%d", &N); N--; solve());
  return 0;
}
