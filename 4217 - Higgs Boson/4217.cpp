using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

struct fraction{
  /*
  represents n/d

  -46340 <= n, d <= 46340; If this is not true an overflow might occur.
  */

  int n, d;
  fraction(int n=0, int d=1) : n(n), d(d) {
    simplify();
  }
  void simplify(){
    if (d != 0){
      int sign = ((n < 0) ^ (d < 0) ? -1 : 1);
      n = abs(n);
      d = abs(d);
      int g = __gcd(n, d);
      if (g){
        n /= g;
        d /= g;
      }
      n *= sign;
    }
  }

  bool positive() const{
    return n*d >= 0;
  }

  bool operator < (const fraction &t) const {
    return n*t.d < d*t.n;
  }

  const fraction operator + (const fraction &t) const {
    return fraction(n*t.d + d*t.n, d*t.d);
  }

  const fraction operator - (const fraction &t) const {
    return fraction(n*t.d - d*t.n, d*t.d);
  }
};

const double pi = 2*acos(0);

int a1, b1, c1, d1, a2, b2, c2, d2;


/*
  Returns true if "time" is a valid parameter for the
  two equations to intercept.
 */
bool isSolution(fraction time){
  if (time.d == 0) return false;
  double t = 1.0*time.n / time.d;
  if (t < 0.0) return false;
  double r1 = a1*t + b1, r2 = a2*t + b2;
  double theta1 = c1*t + d1, theta2 = c2*t + d2;

  theta1 *= pi/180;
  theta2 *= pi/180;

  double x1 = r1*cos(theta1), x2 = r2*cos(theta2);
  double y1 = r1*sin(theta1), y2 = r2*sin(theta2);

#define EPS 1e-9
  return fabs(x1-x2) < EPS && fabs(y1-y2) < EPS;
#undef EPS
}

int main(){
  while (8==scanf("%d%d%d%d%d%d%d%d",&a1,&b1,&c1,&d1,&a2,&b2,&c2,&d2) &&
         (a1||b1||c1||d1||a2||b2||c2||d2)){
    bool solved = false;
    fraction ans(10001, 1);

    //special case, r1 == r2 always
    if (a1 == a2 && b1 == b2){
      if (c1 == c2){
        //depends on d1 and d2
        if (d1 % 360 == d2 % 360){
          printf("0 1\n");
        }else{
          printf("0 0\n");
        }
        continue;
      }


      //try to make r = 0
      fraction t0(-b1,a1);
      if (t0.d != 0 && t0.positive() && isSolution(t0) && t0 < ans){
        ans = t0;
        solved = true;
      }

      /*
        any t in the form : t = (360k + d2 - d1)/(c1 - c2)
        is a solution. Find the smallest that is >= 0.
      */
      fraction t(d2 - d1, c1 - c2);
      fraction delta(360, c1 - c2);
      if (!delta.positive()) delta.n *= -1, delta.simplify();

      while (!t.positive()){
        t = t + delta;
      }

      //now its positive, but it could probably be smaller
      while ((t - delta).positive()){
        t = t - delta;
      }
      t.simplify();
      if (t.d != 0 && t.positive() && isSolution(t) && t < ans){
        ans = t;
        solved = true;
      }

    }else{ //a1 != a2 || b1 != b2
      fraction t0(b2-b1, a1-a2), t1(-b1-b2, a1+a2);
      if (t0.d != 0 && t0.positive() && isSolution(t0) && t0 < ans){
        ans = t0;
        solved = true;
      }
      if (t1.d != 0 && t1.positive() && isSolution(t1) && t1 < ans){
        ans = t1;
        solved = true;
      }
    }
    if (solved){
      printf("%d %d\n", ans.n, ans.d);
    }else printf("0 0\n");
  }
  return 0;
}
