/*
  [NWERC'07] CONTAINERS
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <cmath>

typedef long long LL;

const LL dx = 1000000;

int main () {

  int runs;
  cin>>runs;
  while (runs--) {

    LL N;
    cin>>N;
    N=(N+4)/5;
    
    LL approx=(int)sqrt(2.2*N);
    LL bestA=1LL<<60, bestx=-1, besty=-1;

    for (LL x=approx-dx >? 1; x<approx+dx; x++) {
      LL y = (N+x-1)/x;
      LL A = (10*x+2)*(44*y+4);
      if (A<bestA || (A==bestA && abs(10*x+2-44*y-4) < abs(bestx-besty)))
	bestA=A, bestx=10*x+2, besty=44*y+4;
    }

    if (bestx<besty) swap(bestx,besty);
    cout<<bestx<<" X "<<besty<<" = "<<bestA<<endl; 
  }

  return 0;
}
