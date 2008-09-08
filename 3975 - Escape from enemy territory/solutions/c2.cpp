/*
  [NWERC'07] CONTAINERS
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <cmath>

int main () {

  int runs;
  cin>>runs;
  while (runs--) {

    long long N;
    cin>>N;
    N=(N+4)/5;

    long long bestX=-1,bestY=-1;
    long long bestA = 1LL<<60;
    
    for (long long x=1; x<=N; x++) {
      long long y = (N+x-1)/x;
      if (y<x) break;

      long long X = 10*x+2;
      long long Y = 44*y+4;      
      long long A = X*Y;
      if (A<bestA || (A==bestA && abs(X-Y) < abs(bestX-bestY)))
	bestA=A, bestX=X, bestY=Y;

      X = 10*y+2;
      Y = 44*x+4;      
      A = X*Y;
      if (A<bestA || (A==bestA && abs(X-Y) < abs(bestX-bestY)))
	bestA=A, bestX=X, bestY=Y;
    }

    if (bestX<bestY) swap(bestX,bestY);
    cout<<bestX<<" X "<<bestY<<" = "<<bestA<<endl; 
  }

  return 0;
}
