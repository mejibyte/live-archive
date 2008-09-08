/* Sample solution to Flight Safety from NWERC 2007.
 *
 * Author: Per Austrin
 *
 * Algorithm:
 *
 * Binary search for the answer using a routine to determine whether
 * the route has any points that are at distance d away from land.
 *
 * To implement this routine, consider the shape obtained by taking
 * all points at distance d away from some the boundary of some
 * continent (call this the extended boundary of the continent).  This
 * shape can be modelled as the union of a set of rectangles and
 * circles.  For every segment of the route, we then find all
 * intervals of the segment that intersect with the extended boundary
 * of some continent (using routines for line-rectangle intersection
 * and line-circle intersection).  These intervals are then removed.
 * The remaining intervals of the route segment are either completely
 * inside a continent or completely over water.  Checking each one
 * using a point-in-polygon routine, we can determine whether there
 * was any point at distance d.
 */

#include <cassert>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const double eps = 1e-9;
const bool debug = false;

/* Simple point class. */
struct point {
  double x, y;
  
  point(double _x=0, double _y=0): x(_x), y(_y) {}
  point operator+(const point &p) const { return point(x + p.x, y + p.y); }
  point operator-(const point &p) const { return point(x - p.x, y - p.y); }
  point operator*(double v) const { return point(x * v, y * v); }
  point normal() const { return point(y/abs(), -x/abs()); }
  double dot(const point &p) const { return x*p.x + y*p.y; }
  double cross(const point &p) const { return x*p.y - y*p.x; }
  double abs2() const { return dot(*this); }
  double abs() const { return sqrt(abs2()); }
  
};

typedef vector<point> poly;
typedef pair<point, point> line;
typedef pair<double, double> ival;


/* Compute the intersection of a line with a circle.
 * Returns:
 * - The invalid interval (1,0) if the intersection consists of only one
 *   point or if the intersection does not exist.
 * - The interval (t1, t2) if the intersection is the line between the
 *   points "(1-t1)*L.first + t1*L.second"
 *      and "(1-t2)*L.first + t2*L.second"
 */
ival line_circle_isect(const line &L, const point &C, double r) {
  point dP = L.second - L.first, dLC = L.first - C;
  double c = dLC.abs2() - r*r, b = dP.dot(dLC), a = dP.abs2();
  // the t's we're looking for are the solutions to the equation
  //    a*t^2 + 2*b*t + c = 0
  double disc = b*b - a*c;
  ival res(1,0);
  if (disc < eps) return res;
  disc = sqrt(disc);
  res.first = (-b - disc) / a;
  res.second = (-b + disc) / a;
  return res;
}


/* Compute the intersection of the (infinite) line passing through q1
 * and q2, and the line segment from p1 to p2.
 * Returns:
 * - False if no intersection or if the lines coincide.
 * - True if unique intersection exists.  In that case, t will be set
 *   such that the intersection is given by the point "(1-t)*q1 + t*q2"
 */
bool line_lineseg_isect(const point &q1, const point &q2,
			const point &p1, const point &p2, double &t) {
  point dP = p2-p1, dQ = q2-q1, dPQ = p1-q1;
  double D = dP.cross(dQ);
  // Check if the lines are parallel
  if (fabs(D) < eps) return false;
  t = dP.cross(dPQ) / D;
  // Check that the intersection is not outside the line segment
  double s = dQ.cross(dPQ) / D;
  return s >= 0 && s <= 1;
}


/* Compute the intersection between the line L and the rectangle
 * obtained by making the line segment from m1 to m2, 2*w units wide.
 * Returns:
 * - The invalid interval (1,0) if the intersection is empty.
 * - The interval (t1, t2) if the intersection is the line between the
 *   points "(1-t1)*L.first + t1*L.second"
 *      and "(1-t2)*L.first + t2*L.second"
 */
ival line_rect_isect(const line &L, 
		     const point &m1, const point &m2, double w) {
  // Construct the four corners of the rectangle
  point n = (m2-m1).normal() * w;
  point c[4];
  c[0] = m1 + n;
  c[1] = m1 - n;
  c[2] = m2 - n;
  c[3] = m2 + n;
  ival res(1,0);
  double t;

  // Because rectangles are convex creatures, it suffices to find all
  // intersections with the border of the rectangle and keep the first
  // and the last of these.
  for (int i = 0; i < 4; ++i) {
    if (line_lineseg_isect(L.first, L.second, c[i], c[(i+1)%4], t)) {
      res.first = min(res.first, t);
      res.second = max(res.second, t);
    }
  }

  return res;
}


/* Checks whether the point p lies on the line segment from q1 to q2.
 */
bool on_segment(const point &p, const point &q1, const point &q2) {
  point dq = q2-q1, dp = p-q1;
  return fabs(dq.cross(dp)) < eps &&
    dq.dot(dp) > -eps && dq.dot(dp) < dq.abs2() + eps;
}


/* Checks if the point p is inside the polygon P (counting the border
 * of the polygon as being inside).
 */
bool inside_polygon(const point &p, const poly &P) {
  bool inside = false;
  for (poly::const_iterator it = P.begin(), jt = P.end()-1;
       it != P.end(); jt = it++) {
    if (on_segment(p, *jt, *it)) return true;
    if (((it->x < p.x) ^ (jt->x < p.x)) &&
	((it->y - jt->y)*abs(p.x - jt->x) < (p.y - jt->y)*abs(it->x - jt->x)))
      inside = !inside;
  }
  return inside;
}


vector<poly> continents;
vector<line> route;

/* For debugging purposes.  This is the most recent "far-away" point found in
 * the search, which will be a farthest point when the algorithm terminates.
 */
point last_point_found;

/* Check whether any point along the route is at distance d from the
 * contour of a continent. */
bool has_distance(double d) {

  /* Check for each segment along the route. */
  for (vector<line>::iterator rt = route.begin(); rt != route.end(); ++rt) {
    vector<ival> ivals;
    ival I;

    // Find all intervals of this segment that intersect with the
    // extended boundary of some continent.
    for (vector<poly>::iterator ct = continents.begin();
	 ct != continents.end(); ++ct) {

      for (poly::iterator it = ct->begin(), jt = ct->end()-1;
	   it != ct->end(); jt = it++) {
	I = line_circle_isect(*rt, *it, d);
	if (I.first < I.second) ivals.push_back(I);

	I = line_rect_isect(*rt, *jt, *it, d);
	if (I.first < I.second) ivals.push_back(I);
      }
    }

    sort(ivals.begin(), ivals.end());

    // We now have all the intervals that intersect with the extended
    // boundary of some continent, so now we check the parts of this
    // segment that are not within any such interval.  Each such part
    // is either completely over land or completely over water.
    double x = 0;
    for (vector<ival>::iterator it = ivals.begin(); 
	 x < 1 && it != ivals.end(); ++it) {
      if (it->first > x+eps) {
	// Candidate point found, check that it is not inside a
	// continent
	point p = rt->first*(1-x) + rt->second*x;
	bool inside_continent = false;
	for (vector<poly>::iterator ct = continents.begin();
	     !inside_continent && ct != continents.end(); ++ct)
	  inside_continent = inside_polygon(p, *ct);
	if (!inside_continent) {
	  last_point_found = p;
	  return true;
	}
      }
      x >?= it->second;
    }
  }
  
  return false;
}


bool solve(int P) {
  int C, M, N;
  if (scanf("%d%d", &C, &N) != 2) return false;
  if (C == 0) return false;

  assert(1 <= C && C <= 20);
  assert(1 <= N && N <= 20);

  continents.clear();
  route.clear();

  // Read the route
  point last;
  for (int i = 0; i < N; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    assert(-10000 <= x && x <= 10000);
    assert(-10000 <= y && y <= 10000);
    if (i) route.push_back(line(last, point(x,y)));
    last = point(x,y);
  }

  // Read the continents
  for (int i = 0; i < C; ++i) {
    poly continent;
    int M;
    scanf("%d", &M);
    assert(1 <= M && M <= 30);
    for (int j = 0; j < M; ++j) {
      int x, y;
      scanf("%d%d", &x, &y);
      assert(-10000 <= x && x <= 10000);
      assert(-10000 <= y && y <= 10000);
      continent.push_back(point(x, y));
    }
    continents.push_back(continent);
  }
  
  // Binary search for the answer.
  double lo = 0;
  double hi = 50000;
  while (hi-lo > 1e-10) {
    double m = (lo+hi)/2;
    if (has_distance(m)) lo = m;
    else hi = m;
  }

  printf("%.6lf\n", lo);
  if (debug) {
    fprintf(stderr, "Answer is in [%lf,%lf]\n", lo, hi);
    fprintf(stderr, "(%lf, %lf) is at dist %lf\n",
	    last_point_found.x, last_point_found.y, lo);
  }
  return true;
  
}


int main(void) {
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) solve(i);
  return 0;
}
