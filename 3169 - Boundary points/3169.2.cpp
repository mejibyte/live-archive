/*
  Problem: 3169 - Boundary points
  Algorithm: Convex hull; Graham Scan
  Author: Andrés Mejía-Posada

  Accepted
 */

#include <algorithm>
#include <iostream>
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
using namespace std;

struct point {
  double x, y;
  point(){} point(double x, double y) : x(x), y(y) {}
  bool operator <(const point &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
};
 
point pivot;

ostream& operator<< (ostream& out, const point& c)
{
  out << "(" << c.x << "," << c.y << ")";
  return out;
}

inline double distsqr(const point &a, const point &b){
  return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

inline double dist(const point &a, const point &b){
  return sqrt(distsqr(a, b));
}


// 2D cross product.
// Return a positive value, if ABC makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
double cross(const point &a, const point &b, const point &c){
  double d = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  if (fabs(d) < 1e-9) return 0.0;
  return d;
}



//Self < that si esta a la derecha del segmento Pivot-That
bool angleCmp(const point &self, const point &that){
  double t = cross(pivot, that, self);
  if (t < 0.0) return true;
  if (t == 0){
    //Self < that si está más cerquita
    return (distsqr(pivot, self) < distsqr(pivot, that));
  }
  return false;
}

//vector p tiene los puntos ordenados anticlockwise
vector<point> graham(vector<point> p){
  //Metemos el más abajo más a la izquierda en la posición 0
  for (int i=1; i<p.size(); ++i){
    if (p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x ))
      swap(p[0], p[i]);
  }
  
  pivot = p[0];
  sort(p.begin(), p.end(), angleCmp);

  //Ordenar por ángulo y eliminar repetidos.
  //Si varios puntos tienen el mismo angulo el más lejano queda después en la lista
  vector<point> chull(p.begin(), p.begin()+3);

  //Ahora sí!!!
  for (int i=3; i<p.size(); ++i){
    while ( chull.size() >= 2 && cross(chull[chull.size()-2], chull[chull.size()-1], p[i]) <= 0){
      chull.erase(chull.end() - 1);
    }
    chull.push_back(p[i]);
  }

  return chull;
}

int main(){
  string s;
  while (getline(cin, s)){
    stringstream splitter(s);
    string pnt;
    vector<point> poly;
    while (splitter >> pnt){
      assert(pnt.size() > 3);
      pnt[0] = pnt[pnt.size()-1] = pnt[pnt.find(',')] = ' ';
      stringstream sin(pnt);
      double x, y;
      sin >> x >> y;
      poly.push_back(point(x, y));
    }

    vector<point> ans = graham(poly);
    ans.push_back(ans[0]);
    cout << "(" << ans.front().x << "," << ans.front().y << ")";
    for (int i=1; i<ans.size(); ++i){
      cout << " (" << ans[i].x << "," << ans[i].y << ")";
    }
    cout << endl;
  }
  return 0;
}
