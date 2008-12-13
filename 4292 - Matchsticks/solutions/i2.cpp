/* NWERC 2008: Sample solution to "Wildwater Rafting"
 * Author: Per Austrin
 *
 * Algorithm: brute force
 */
#include <cassert>
#include <cstdio>
#include <cmath>

using namespace std;

struct P {
  double x, y;
  P(double x=0, double y=0): x(x), y(y) {}
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(double f) const { return P(f*x, f*y); }
  double dot(const P& p) { return x*p.x + y*p.y;}
  double dist2() { return dot(*this); }
};

double d(P p0, P p1, P q) {
  double t = 0 >? (p1-p0).dot(q-p0) / (p1-p0).dist2() <? 1;
  return sqrt((p0*(1-t) - p1*-t - q).dist2());
}

double d(P p0, P p1, P q0, P q1) {
  return d(p0, p1, q0) <? d(p0, p1, q1) <? d(q0, q1, p0) <? d(q0, q1, p1);
}

void rp(int &N, P *p) {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
}

void solve() {
  int N1, N2;
  P P1[200], P2[200];
  rp(N1, P1);
  rp(N2, P2);
  double res = 1e30;
  for (int i1 = 0, j1 = N1-1; i1 < N1; j1 = i1++)
    for (int i2 = 0, j2 = N2-1; i2 < N2; j2 = i2++)
      res <?= d(P1[i1], P1[j1], P2[i2], P2[j2]);
  printf("%.9lf\n", res/2);
}

int main(void) {
  int N;
  for (scanf("%d", &N); N--; solve());
  return 0;
}
