/*
  [NWERC'08] WILDWATER RAFTING
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

struct point { int x,y; };

point operator - (point p, point q) { return (point) {p.x-q.x, p.y-q.y}; }
int operator * (point p, point q) { return p.x*q.x + p.y*q.y; }
int operator ^ (point p, point q) { return p.x*q.y - p.y*q.x; }

double dist (point p, point q1, point q2) {
  
  if ((p-q1)*(q2-q1) < 0) return sqrt((p-q1)*(p-q1));
  if ((p-q2)*(q1-q2) < 0) return sqrt((p-q2)*(p-q2));
  return abs((p-q1)^(q2-q1)) / sqrt((q2-q1)*(q2-q1));
}

vector<point> readpolygon() {
  
  int N; cin>>N;
  vector<point> p(N);
  for (int i=0; i<N; i++) cin>>p[i].x>>p[i].y;
  return p;
}

int main () {

  int runs;
  cin>>runs;

  while (runs--) {

    vector<point> p1 = readpolygon();
    vector<point> p2 = readpolygon();
    
    double res = 1e100;
    for (int i=0; i<p1.size(); i++)
      for (int j=0; j<p2.size(); j++) {
	res <?= dist(p1[i],p2[j],p2[(j+1)%p2.size()]);
	res <?= dist(p2[j],p1[i],p1[(i+1)%p1.size()]);
      }
    
    cout<<setprecision(10)<<res/2<<endl;
  }

  return 0;
}
