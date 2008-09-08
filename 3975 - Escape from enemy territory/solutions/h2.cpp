/* Sample solution to Obfuscation from NWERC 2007
 *
 * Author: Per Austrin
 *
 * Algorithm: standard DP
 *
 * Note: I've been very lazy and wouldn't be surprised if this
 * solution turns out to be a bit too slow.
 */
#include <cstdio>
#include <map>
struct hist { char a, b; std::map<char,int> f;
  bool operator<(const hist &h) const {return a!=h.a?a<h.a:b!=h.b?b<h.b:f<h.f;}
  hist(char *w) { a = *w; for (; *w; b = *w++) ++f[*w]; } };
typedef std::map<hist,int> words;
int main(void) {
  int i, T, N, dp[1100];
  char W[1100], dict[10100][110];
  for (scanf("%d", &T); scanf("%s%d", W, &N), T--; ) {
    words lookup; hist h(W); words::iterator it;
    for (i = 0; i < N && scanf("%s", dict[i]); ++i)
      if ((it = lookup.find(h = hist(dict[i]))) == lookup.end()) lookup[h] = i;
      else it->second = -1;
    for (dp[N = strlen(W)] = 0; dp[N-1] = -2, h.f.clear(), N--; )
      for (h.a = W[i = N]; ++h.f[W[i]], h.b = W[i], W[i]; ++i)
	if (dp[i+1] >= -1 && (it = lookup.find(h)) != lookup.end())
	  dp[N] = (dp[N] >= -1 || dp[i+1] < 0) ? -1 : it->second;
    if (dp[0] < 0) printf("%s\n", dp[0] == -1 ? "ambiguous" : "impossible");
    else for (int i = 0; W[i]; i+=strlen(dict[dp[i]]))
      printf("%s%c", dict[dp[i]], W[i+strlen(dict[dp[i]])] ? ' ' : '\n');
  }
  return 0;
}
