/*
  [NWERC'08] DISGRUNTLED JUDGE
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>

const int p = 73;
const int q = 137;
const int M = p*q;

int mod (int a) { return (a%M+M)%M; }

int pow (int a, int b) {
  int res=1;
  while (b) { if (b&1) res=mod(res*a); a=mod(a*a); b>>=1; }
  return res;
}

int inv (int a) { return pow(a,M-p-q); }

int main () {

  int N;
  cin>>N;

  vector<int> x(N);
  for (int i=0; i<N; i++) cin>>x[i];

  for (int a=0; a<M; a++) {
    int b = mod(x[1] - mod(a*a)*x[0]) * inv(a+1);
      
    int y=x[0], ok=1;
    
    for (int i=0; i<N && ok; i++) {
      if (y!=x[i]) { ok=0; break; }
      y = (a*y+b)%M;
      y = (a*y+b)%M;
    }
    
    if (ok) {
      for (int i=0; i<N; i++) cout<<(a*x[i]+b)%M<<endl;
      break;
    }
  }
  
  return 0;
}
