/*
  Empezado por mí, terminado por Arcila
*/
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;

struct point{
  double x,y;
};

/*
  Returns positive if a-b-c make a left turn.
  Returns negative if a-b-c make a right turn.
  Returns 0.0 if a-b-c are colineal.
 */
double turn(const point &a, const point &b, const point &c){
  double z = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
  if (fabs(z) < 1e-9) return 0.0;
  return z;
}

/*
  Returns true if polygon p is convex.
  False if it's concave or it can't be determined.
 */
bool isConvex(const vector<point> &p){
  int n = p.size();
  int mask = 0;
  for (int i=0; i<n; ++i){
    int j=(i+1)%n;
    int k=(i+2)%n;
    double z = turn(p[i], p[j], p[k]);
    if (z < 0.0){
      mask |= 1;
    }else if (z > 0.0){
      mask |= 2;
    }
    if (mask == 3) return false;
  }
  return mask != 0;
}

/*
  Returns true if point a is inside polygon p.
  Note that if point a lies on the border of p it
  is considered outside.
 */
bool inside(const vector<point> &p, const point &a){
  int n = p.size();
  int mask = 0;
  for (int i=0; i<n; ++i){
    int j = (i+1)%n;
    double z = turn(p[i], p[j], a);
    if (z < 0.0){
      mask |= 1;
    }else if (z > 0.0){
      mask |= 2;
    }else if (z == 0.0) return false;
    if (mask == 3) return false;
  }
  return mask != 0;

}
/*
  Returns double value of the "determinante"
 */
inline double det(const point &one,const point &two,const point &three){
  return one.x*(two.y-three.y)-one.y*(two.x-three.x)+(two.x*three.y-two.y*three.x);
}
/*
  Returns true if I can place circle at point "peg" with radius "radius"
  such that it's inside polygon "p".
 */
bool check(const vector<point> &p, const point &peg, const double &radius){
  if (!inside(p, peg)) return false;
  //Revisar aquí que la distancia entre el punto peg y la arista (p[i], p[(i+1)%n]) sea <=  radius.
  int n=p.size();
  for(int i=0;i<n;++i){
    if(fabs(det(p[i],p[(i+1)%n],peg)/sqrt(pow(p[i].x-p[(i+1)%n].x,2.0)+pow(p[i].y-p[(i+1)%n].y,2.0))) < radius){
      return false;
    }
  }
  return true;
}

int main(){
  int n;
  while (cin >> n && n >= 3){
    double pegRadius;
    point peg;
    cin >> pegRadius >> peg.x >> peg.y;
    assert(pegRadius > 0.0);
    vector<point> p(n);
    for (int i=0; i<n; ++i){
      cin >> p[i].x >> p[i].y;
    }
    if (!isConvex(p)){
      cout << "HOLE IS ILL-FORMED" << endl;
    }else{
      cout << "PEG WILL " << (check(p, peg, pegRadius) ? "" : "NOT ") << "FIT" << endl;
    }

  }
  return 0;
}
