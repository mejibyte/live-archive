/*
  [NWERC'08] DISGRUNTLED JUDGE
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>

const int M = 10001;

int main () {

  int N;
  cin>>N;

  vector<int> x(N);
  for (int i=0; i<N; i++) cin>>x[i];

  for (int a=0; a<M; a++)
    for (int b=0; b<M; b++) {

      int y=x[0], ok=1;
      
      for (int i=0; i<N && ok; i++) {
	if (y!=x[i]) { ok=0; break; }
	y = (a*y+b)%M;
	y = (a*y+b)%M;
      }

      if (ok) {
	for (int i=0; i<N; i++) cout<<(a*x[i]+b)%M<<endl;
	return 0;
      }
    }
    
  return 1;
}
