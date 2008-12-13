using namespace std;

#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

typedef double coord;

const double EPS = 1E-8;

const int HIT_INTERSECTS = 1;

const int LINE    = 0;
const int SEGMENT = 1;

class point {
public:
	coord x, y;
  
	point() { x = y = 0; }
	point(coord x1, coord y1) { x = x1; y = y1; }

	point operator +=(point a) { x += a.x; y += a.y; return *this; }
	point operator -=(point a) { x -= a.x; y -= a.y; return *this; }
	point operator *=(coord a) { x *= a;   y *= a;   return *this; }
	point operator /=(coord a) { x /= a;   y /= a;   return *this; }
	int   operator ==(point a) { return x==a.x && y==a.y; }
	int   operator !=(point a) { return x!=a.x || y!=a.y; }
};

point operator *(coord x, point a) { return a *= x; }
point operator *(point a, coord x) { return a *= x; }
point operator /(point a, coord x) { return a /= x; }
point operator +(point a, point b) { return a += b; }
point operator -(point a, point b) { return a -= b; }
coord operator *(point a, point b) { return a.x*b.x + a.y*b.y; }

coord cross(point a, point b) { return a.x*b.y - a.y*b.x; }
double length(point a) { return sqrt((double)(a*a)); }
point perp(point a) { return point(-a.y,a.x); }

class line {
public:
	point p1, p2;

	line() { p1 = p2 = point(); }
	line(point q1, point q2) { p1 = q1; p2 = q2; }

	int  operator ==(line a) { return (p1==a.p1 && p2==a.p2) || (p1==a.p2 && p2==a.p1); }
};

double dist(point a, line b, int segment = 0)
{
	point db = b.p2 - b.p1;
	
	if ( segment && ((b.p1-a)*db)*((b.p2-a)*db)>0 )
		return min(length(b.p1-a),length(b.p2-a));
	
	a -= db*((a-b.p1)*db)/(db*db);
	return length(b.p1 - a);
}

double dist(line a, line b)
{
	double res;

	res   = dist(a.p1,b,1);
	res <?= dist(a.p2,b,1);
	res <?= dist(b.p1,a,1);
	res <?= dist(b.p2,a,1);

	return res;
}

int equal(line a, line b)
{
	return dist(a.p1,b)<EPS && dist(a.p1,b)<EPS;
}

int intersect(line a, line b, point *sectpoint, int segment = 0)
{
	// directions of lines
	point da = a.p2 - a.p1;
	point db = b.p2 - b.p1;
	double eps;
	
	if ( length(da)<EPS || length(db)<EPS ) return 0;
	
	// false if lines are parallel
	if ( fabs(cross(da,db)/(length(da)*length(db)))<EPS ) return 0;

	// calc intersection point (need coord to be floating point!)
	if ( sectpoint!=NULL ) *sectpoint = b.p1 + (cross(da,a.p1-b.p1)/cross(da,db))*db;

	// return false if line segments not really cross
	if ( segment ) {
		eps = HIT_INTERSECTS ? +EPS : -EPS;
		if ( cross(da,b.p1-a.p1)*cross(da,b.p2-a.p1)/(da*da)>eps ) return 0;
		if ( cross(db,a.p1-b.p1)*cross(db,a.p2-b.p1)/(db*db)>eps ) return 0;
	}
	
	return 1;
}

vector<point> side[2];

const int maxcoord = 1000;
const int minpoint = 3;
const int maxpoint = 100;

int main()
{
	int nruns;
	scanf("%d\n",&nruns);

	for(int run=0; run<nruns; run++) {

		for(int s=0; s<2; s++) {
			int n;
			scanf("%d\n",&n);
			if ( n<minpoint || n>maxpoint ) {
				printf("#points = %d invalid\n",n);
				return -1;
			}
			
			side[s] = vector<point>(n);
			for(int i=0; i<n; i++) {
				scanf("%lf %lf\n",&side[s][i].x,&side[s][i].y);
				if ( abs(side[s][i].x)>maxcoord ||
					 abs(side[s][i].y)>maxcoord ) {
					printf("maxcoord too large\n");
					return -1;
				}
			}
		}

		// Check for intersections of each polygon with itself:
		// (inter-polygon intersections will result in radius 0 tested below)
		for(int s=0; s<2; s++) {
			for(int i=0; i<side[s].size(); i++) {
				for(int j=0; j<i-1; j++) {
					if ( j==0 && i==side[s].size()-1 ) continue;
					line l1(side[s][i],side[s][(i+1)%side[s].size()]);
					line l2(side[s][j],side[s][(j+1)%side[s].size()]);
					if ( intersect(l1,l2,NULL,1) ) {
						printf("self intersecting polygon %d: %d - %d\n",s,i,j);
						return -1;
					}
				}
				point p1 = side[s][i] - side[s][(i+1)%side[s].size()];
				int j = i+1;
				point p2 = side[s][(j+1)%side[s].size()] - side[s][j];
				if ( fabs(atan2(p1.y,p1.x)-atan2(p2.y,p2.x))<1E-7 ) {
					printf("self intersecting polygon %d: %d - %d\n",s,i,j);
					return -1;
				}
			}
		}

		// Check that side[0] is inner polygon:
		line l(side[0][0],side[0][0]+point(2*maxcoord+1,0.5));
		int nsect = 0;
		for(int i=0; i<side[1].size(); i++) {
			line m(side[1][i],side[1][(i+1)%side[1].size()]);
			if ( intersect(l,m,NULL,1) ) nsect++;
		}
		if ( nsect%2==0 ) {
			printf("first polygon is not the inner polygon\n");
			return -1;
		}
		
		double maxd = 0.99999E10;
		
		for(int i=0; i<side[0].size(); i++)
			for(int j=0; j<side[1].size(); j++) {
				line l1(side[0][i],side[0][(i+1)%side[0].size()]);
				line l2(side[1][j],side[1][(j+1)%side[1].size()]);

				double d = dist(l1,l2);
				if ( d<maxd ) {
					maxd = d;
// 					printf("new max = %10.6lf @ %+4d,%+4d - %+4d,%+4d # %+4d,%+4d - %+4d,%+4d\n",
// 						   maxd/2,
// 						   l1.p1.x,l1.p1.y,l1.p2.x,l1.p2.y,
// 						   l2.p1.x,l2.p1.y,l2.p2.x,l2.p2.y);
				}
			}

		if ( maxd<EPS ) {
			printf("distance too small: %le < %le\n",maxd,EPS);
			return -1;
		}
		printf("%.9lf\n",maxd/2);
	}
	
	return 0;
}
