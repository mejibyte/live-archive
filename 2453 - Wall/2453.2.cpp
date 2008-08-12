/*
  Accepted. Andrew's Monotone chain.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <stdio.h>

using namespace std;


const double pi = 2*acos(0);
//const double pi = 3.14159265;

struct point{
  int x,y;
  point() {}
  point(int X, int Y) : x(X), y(Y) {}
  bool operator < (const point &p) const {
    return (x < p.x || (x == p.x &&y < p.y));
  }
};


ostream& operator<< (ostream& out, const point& c)
{
  out << "(" << c.x << "," << c.y << ")";
  return out;
}

inline double dist(const point &a, const point &b){
  return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}



// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
long long crossproduct(const point &O, const point &A, const point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is NOT the same as the first one.
vector<point> convexHull(vector<point> P)
{
	long long n = P.size(), k = 0;
	vector<point> H(2*n);
 
	// Sort Points lexicographically
	sort(P.begin(), P.end());
 
	// Build lower hull
	for (long long i = 0; i < n; i++) {
		while (k >= 2 && crossproduct(H[k-2], H[k-1], P[i]) < 0) k--;
		H[k++] = P[i];
	}
 
	// Build upper hull
	for (long long i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && crossproduct(H[k-2], H[k-1], P[i]) < 0) k--;
		H[k++] = P[i];
	}
 
	H.resize(k-1);
	return H;
}

int main(){
  int cases;
  cin >> cases;
  bool first = true;
  while (cases--){
    if (!first) cout << endl;
    first = false;
    int n, l;
    cin >> n >> l;
    vector<point> p;
    for (int i=0; i<n; ++i){
      int x, y;
      cin >> x >> y;
      p.push_back(point(x,y));      
    }

    vector<point> chull = convexHull(p);
     
    /*cout << "chull es:  " << endl;
      for (int i=0; i<chull.size(); ++i){
      cout << chull[i] << " ";
      }
      cout <<  endl;*/

    double perimeter = 0.0;
    for (int i=0; i<chull.size(); ++i){
      int j = (i+1)%chull.size();
      perimeter += dist(chull[i], chull[j]);
      //cout << " sumando " << hypot(p[i].y - p[j].y, p[i].x - p[j].x) << " entre " << p[i] << " y " << p[j] << endl;
    }

    //cout << "Perimeter es: " << perimeter << endl;
      
    //printf("%.0f\n", floor(perimeter + 2*pi*l + 0.5));
    printf("%.0lf\n", perimeter + 2*pi*l);
  }
  return 0;
}
