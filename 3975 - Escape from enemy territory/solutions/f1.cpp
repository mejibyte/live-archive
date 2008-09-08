/*
  [NWERC'07] FLIGHT SAFETY
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

const double eps = 1e-9;

typedef pair<double,double> PDD;

struct point {
  double x,y;
  point(): x(0), y(0) {}
  point(double _x, double _y): x(_x), y(_y) {}
};

int N,C;
vector<point> r;
vector<vector<point> > p;

point operator * (double x, point a) { return point(x*a.x, x*a.y); }
point operator + (point a, point b) { return point(a.x+b.x, a.y+b.y); }
point operator - (point a, point b) { return point(a.x-b.x, a.y-b.y); }
double operator * (point a, point b) { return a.x*b.x + a.y*b.y; }
double operator ^ (point a, point b) { return a.x*b.y - a.y*b.x; }
point norm (point a) { return 1/sqrt(a*a) * point(a.y,-a.x); }
				     
void read () {
  
  cin>>C>>N;
  r=vector<point>(N);
  p=vector<vector<point> >(C);
  
  for (int i=0; i<N; i++)
    cin>>r[i].x>>r[i].y;

  for (int i=0; i<C; i++) {
    int n;
    cin>>n;
    p[i]=vector<point>(n);
    
    for (int j=0; j<n; j++)
      cin>>p[i][j].x>>p[i][j].y;

    p[i].push_back(p[i][0]);
    
    double area=0;
    for (int j=0; j<n; j++)
      area += p[i][j] ^ p[i][j+1];

    if (area<0) reverse(p[i].begin(), p[i].end());
  }  
}

vector<PDD> intervalspolygon (point a, point b, vector<point> p) {

  vector<double> ts;
  ts.push_back(0);
  ts.push_back(1);
  
  for (int i=0; i<p.size()-1; i++) {
    point c=p[i], d=p[i+1];

    if (fabs(b-a^d-c) < eps) continue;

    double t = (d-c^a-c) / (b-a^d-c);
    double s = (b-a^a-c) / (b-a^d-c);
    if (t<-eps || t>1+eps) continue;
    if (s<-eps || s>1+eps) continue;

    ts.push_back(t);
  }
  
  sort(ts.begin(),ts.end());
  vector<PDD> res;

  for (int i=0; i<ts.size()-1; i++) {
    point c = a + (ts[i]+ts[i+1])/2 * (b-a);
    point d = c - point(100000,1);

    int cnt=0;
    for (int j=0; j<p.size()-1; j++)
      if ((c-p[j]^p[j+1]-p[j]) * (d-p[j]^p[j+1]-p[j]) < 0 &&
	  (p[j]-c^d-c) * (p[j+1]-c^d-c) < 0) cnt++;      

    if (cnt%2 == 1) res.push_back(make_pair(ts[i],ts[i+1]));
  }
  
  return res;
}

vector<PDD> intervalscircle (point a, point b, point p, double r) {
  double A = (b-a)*(b-a);
  double B = 2*(b-a)*(a-p);
  double C = (a-p)*(a-p) - r*r;

  vector<PDD> res;
  if (B*B-4*A*C < 0) return res;

  double t1 = (-B-sqrt(B*B-4*A*C)) /2/A;
  double t2 = (-B+sqrt(B*B-4*A*C)) /2/A;

  if (t2<-eps || t1>1+eps) return res;

  res.push_back(make_pair(max(t1,0.0),min(t2,1.0)));
  return res;
}

void solve () {

  double lo=0, hi=40000;
  
  for (int times=0; times<50; times++) {

    double dist = (lo+hi)/2;
    int ok=1;
    
    for (int i=0; i<N-1; i++) {

      vector<PDD> ivals;
      
      for (int j=0; j<C; j++) {
	vector<PDD> tmp = intervalspolygon(r[i], r[i+1], p[j]);
	ivals.insert(ivals.end(), tmp.begin(), tmp.end());
      }

      for (int j=0; j<C; j++)
	for (int k=0; k<p[j].size()-1; k++) {
	  point a = p[j][k];
	  point b = p[j][k+1];
	  point n = norm(b-a);
	  
	  vector<point> sq;
	  sq.push_back(a + dist * n);
	  sq.push_back(a - dist * n);
	  sq.push_back(b - dist * n);
	  sq.push_back(b + dist * n);
	  sq.push_back(a + dist * n);

	  vector<PDD> tmp = intervalspolygon(r[i], r[i+1], sq);
	  ivals.insert(ivals.end(), tmp.begin(), tmp.end());

	  tmp = intervalscircle(r[i], r[i+1], p[j][k], dist);
	  ivals.insert(ivals.end(), tmp.begin(), tmp.end());
	}

      sort(ivals.begin(),ivals.end());

      double to=0;
      
      for (int j=0; j<ivals.size(); j++) {
	if (ivals[j].first > to+eps) ok=0;
	to >?= ivals[j].second;
      }
      if (to < 1-eps) ok=0;

      if (!ok) break;
    }

    if (ok) hi=dist; else lo=dist;
  }

  cout<<setprecision(10)<<lo<<endl;
}

int main () {

  int runs;
  cin>>runs;
  
  while (runs--) {
    read();
    solve();
  }
  
  return 0;
}
