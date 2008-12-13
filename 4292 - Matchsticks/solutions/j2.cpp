/* NWERC 2008: Sample solution to "Shuffle"
 * Author: Per Austrin
 *
 * Algorithm: interval union
 */
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int, int> pii;
int S, N, last[200000];
void solve() {
  scanf("%d%d", &S, &N);
  memset(last, -1, sizeof(last));
  vector<pii> excl;
  for (int i = 0, s, x, y; i < N && scanf("%d", &s); last[s] = i++)
    if (last[s] != -1 && i-last[s] < S)
      if ((x = last[s]%S) > (y = i%S)) excl.push_back(pii(y, x));
      else excl.push_back(pii(0, x)), excl.push_back(pii(y, S));
  sort(excl.begin(), excl.end());
  int at = 0, res = 0;
  for (int i = 0; i < excl.size(); at >?= excl[i++].second)
    res += (excl[i].first-at) >? 0;
  printf("%d\n", res+S-at);
}

int main(void) {
  int N;
  for (scanf("%d", &N); N--; solve());
  return 0;
}
