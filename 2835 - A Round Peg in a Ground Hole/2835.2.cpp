/*
  Author: Andrés Mejía-Posada + Sebastián Arcila-Valenzuela
  http://blogaritmo.factorcomun.org

  Accepted
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

int n;

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

inline double dist(const point &a, const point &b){
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

inline double distsqr(const point &a, const point &b){
  return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}


/*
  Returns true if polygon p is convex.
  False if it's concave or it can't be determined.
 */
bool isConvex(const vector<point> &p){
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
  Returns the closest distance between point pnt and the line that passes through points a & b
  Idea by: http://local.wasp.uwa.edu.au/%7Epbourke/geometry/pointline/
 */
double distance_point_to_line(const point &a, const point &b, const point &pnt){
  double u = ((pnt.x - a.x)*(b.x - a.x) + (pnt.y - a.y)*(b.y - a.y)) / distsqr(a, b);
  point intersection;
  intersection.x = a.x + u*(b.x - a.x);
  intersection.y = a.y + u*(b.y - a.y);
  return dist(pnt, intersection);
}

/*
  Returns true if I can place circle at point "peg" with radius "radius"
  such that it's inside polygon "p".
 */
bool check(const vector<point> &p, const point &peg, const double &radius){
  if (!inside(p, peg)) return false;
  //Revisar aquí que la distancia entre el punto peg y la arista (p[i], p[(i+1)%n]) sea <=  radius.
  for (int i=0; i<n; ++i){
    int j = (i+1)%n;
    double z = distance_point_to_line(p[i], p[j], peg);
    if (z < radius){
      return false;
    }
  }
  return true;
}

int main(){
  while (scanf("%d", &n) == 1 && n >= 3){
    double pegRadius;
    point peg;
    scanf("%lf %lf %lf", &pegRadius, &peg.x, &peg.y);
    vector<point> p(n);
    for (int i=0; i<n; ++i){
      scanf("%lf %lf", &p[i].x,  &p[i].y);
    }
    if (!isConvex(p)){
      puts("HOLE IS ILL-FORMED");
    }else{
      printf("PEG WILL %sFIT\n", (check(p, peg, pegRadius) ? "" : "NOT "));
    }

  }
  return 0;
}
