/*
  [NWERC'07] TOWER PARKING
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>

const int Telev = 10;
const int Tbelt = 5;

int main () {
  int runs;
  cin>>runs;
  while (runs--) {
    int Y,X;
    cin>>Y>>X;

    vector<int> xi(Y*X), yi(Y*X);
    int N=0;
    for (int y=0; y<Y; y++)
      for (int x=0; x<X; x++) {
	int n;
	cin>>n;
	N>?=n--;
	if (n>=0) xi[n]=x, yi[n]=y;
      }

    long long res=0;
    vector<int> pos(Y, 0);
    
    for (int i=0; i<N; i++) {
      int diff = abs(pos[yi[i]] - xi[i]);
      pos[yi[i]] = xi[i];
      res += min(diff, X-diff)*Tbelt + 2*yi[i]*Telev;
    }

    cout<<res<<endl;
  }
  
  return 0;   
}
