#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

struct Point{
  int x, y;
  bool operator < (const Point &p) const {
    return (x < p.x || (x == p.x && y < p.y));
  }
  bool operator == (const Point &p) const {
    return (x == p.x && y == p.y);
  }
};

void printPnt(const Point &p);

// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
int cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

//Retorna una lista de los puntos que no están en el convex hull en orden lexicografico
vector<Point> unconvexHull(vector<Point> P)
{

	int n = P.size(), k = 0;
	vector<Point> H(2*n);
 
	// Sort Points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; i++) {
	  while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0){
	    k--;
	  }
	  H[k++] = P[i];
	}
 
	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
	  while (k >= t && cross(H[k-2], H[k-1], P[i]) < 0){
	    k--;
	  }
	  H[k++] = P[i];
	}
 
	H.resize(k);
	/*cout << "El convex hull es: ";
	for (int i=0; i<H.size(); i++){
	  printPnt(H[i]); cout << " ";
	}
	cout << endl<<endl;*/

	H.pop_back();

	int i, //iterador para H
	  j=0;   //iterador para P
	
	for (; j<P.size(); ++j){
	  for (i=0; i<H.size(); ++i){
	    if (P[j] == H[i]){
	      P.erase(P.begin()+j);
	      --j;
	      break;
	    }
	  }
	}
	return P;
}

void printPnt(const Point &p){
  cout << "(" << p.x << "," << p.y << ")";
}

int main(){  
  int n;
  cin >> n;
  while (n){
    //procesar caso
    vector<Point> g(n);
    for (int i=0; i<n; ++i){
      int x, y;
      cin >> x >> y;
      g[i].x = x;
      g[i].y = y;
    }
    /*cout << "g.size() es: " << g.size() << endl;
    for (int i=0; i<n; ++i){
      printPnt(g[i]);
      cout << " ";
    }
    cout << endl; */
    int capas = 1;
    vector<Point> chull = unconvexHull(g);
    while (chull.size() > 0){
      chull = unconvexHull(chull);
      assert(chull.size() == 0 || chull.size() >= 3);
      ++capas;
    }
    if (capas % 2 == 0){
      cout << "Do not take this onion to the lab!\n";
    }else{
      cout << "Take this onion to the lab!\n";
    }
    /*cout << "chull.size() es: " << chull.size() << endl;
    for (int i=0; i<chull.size(); ++i){
      printPnt(chull[i]);
      cout << " ";
    }
    cout << endl;*/
    
    cin >> n;
  }
  return 0;
}
