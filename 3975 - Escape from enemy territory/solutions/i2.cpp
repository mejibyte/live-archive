/*
  [NWERC'07] TOWER PARKING
  by: Jan Kuipers

  O(L^2*W^2) solution to confirm time limits
*/

using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

const int Telev = 10;
const int Tbelt = 5;

int main () {
  int runs;
  cin>>runs;
  while (runs--) {
    int Y,X;
    cin>>Y>>X;

    vector<vector<int> > car(Y, vector<int>(X));
    for (int y=0; y<Y; y++)
      for (int x=0; x<X; x++)
	cin>>car[y][x];

    int res=0;
    
    for (int n=1; n<Y*X; n++) {
      int cary=-1, carx=-1;
      for (int y=0; y<Y; y++)
	for (int x=0; x<X; x++)
	  if (car[y][x]==n) cary=y, carx=x;

      if (cary==-1) break;

      res += Tbelt * min(carx, X-carx);
      res += 2 * Telev * cary;

      rotate(car[cary].begin(), car[cary].begin()+carx, car[cary].end());
    }

    cout<<res<<endl; 
  }

  return 0;
}
