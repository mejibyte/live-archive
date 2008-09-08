using namespace std;

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <utility>
#include <functional>
#include <numeric>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define PB push_back
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define REP(i, n) for(int i=0; i<(n); ++i)
#define REPD(i, n) for(int i=(n)-1; i>=0; --i)
#define FOR(i, b, e) for(typeof(e) i=b; i!=e; ++i)

typedef long long LL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef istringstream ISS;

typedef pair<double,double> Point;
typedef pair<Point, Point> Line;
#define _X first
#define _Y second

int N;
vector<Line> lines;
VI ind;
VI heights;

double operator*(Point a, Point b) {
  return a._X*b._X+a._Y*b._Y;
}

Point operator-(Point a, Point b) {
  return Point(a._X-b._X,a._Y-b._Y);
}

Point operator+(Point a, Point b) {
  return Point(a._X+b._X,a._Y+b._Y);
}

double intersect(Line l1, Line l2) {
  double x=0.0/0.0;
  Point n1=l1.second-l1.first, n2=l2.second-l2.first;
  swap(n1.first, n1.second); n1.first=-n1.first;
  swap(n2.first, n2.second); n2.first=-n2.first;
  double n1l2f=n1*(l2.first-l1.first);
  double n1l2s=n1*(l2.second-l1.first);
  double n2l1f=n2*(l1.first-l2.first);
  double n2l1s=n2*(l1.second-l2.first);
  if(n1l2f<0.0 && n1l2s<0.0) return x;
  if(n1l2f>0.0 && n1l2s>0.0) return x;
  if(n2l1f<0.0 && n2l1s<0.0) return x;
  if(n2l1f>0.0 && n2l1s>0.0) return x;
  double s=(n1*(l1.first-l2.first))/(n1*(l2.second-l2.first));
  if(l2.first._X+s*(l2.second-l2.first)._X>100000.0) {
    printf("Failed (%lf,%lf)-(%lf,%lf)\n", l2.first._X, l2.first._Y, l2.second._X, l2.second._Y);
  }
  return l2.first._X+s*(l2.second-l2.first)._X;
}
    
void go() {
  scanf("%d", &N);
  lines.clear(); ind.clear();
  heights.clear(); heights.resize(N);
  REP(i, N) {
    int n;
    scanf("%d %d", &heights[i], &n);
    vector<Point> points(n);
    REP(j, n) scanf("%lf %lf", &points[j]._X, &points[j]._Y);
    REP(j, n) {lines.PB(Line(points[j], points[(j+1)%n])); ind.PB(i);}
  }
  Line walk(Point(0.0,0.0), Point(100000.0, 0.001));
  typedef pair<double, int> PDI;
  vector<PDI> cross;
  REP(i, SZ(lines)) {
    double x=intersect(walk, lines[i]);
    if(x!=x) continue;
    //printf("Index %d intersected (%lf,%lf)-(%lf,%lf)\n",ind[i],lines[i].first._X,lines[i].first._Y,lines[i].second._X,lines[i].second._Y);
    cross.PB(PDI(x,ind[i]));
  }
  sort(ALL(cross));
  /*
  REP(i, SZ(cross)) {
    printf("Index %d intersected x=%lf\n",cross[i].second,cross[i].first);
  }
  */
  VI hind;
  REP(i, SZ(cross)) {
    if(!hind.empty() && hind.back()==cross[i].second) hind.pop_back();
    else hind.PB(cross[i].second);
  }
  /*REP(i, SZ(hind)) {
    printf("Index %d\n",hind[i]);
}*/
  int s=SZ(hind);
  if(s<2) printf("%d %d\n",0,0);
  else {
    int h=heights[hind[0]];
    int asc=0, des=0;
    FOR(i, 1, s) {
      if(heights[hind[i]]>h) asc+=heights[hind[i]]-h;
      else des+=h-heights[hind[i]];
      h=heights[hind[i]];
    }
    printf("%d %d\n",asc,des);
  }
}

int main() {
  int nruns;
  scanf("%d", &nruns);
  while(nruns--) go();
  return 0;
}
