/*
  [NWERC'07] MARCH OF THE PENGUINS
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>

int N;
vector<vector<int> > c;
vector<int> u;

int go (int n, int sour, int sink) {
  if (n==sour) u=vector<int>(2*N,0);
  if (n==sink) return 1;
  u[n]=1;

  for (int i=0; i<2*N; i++)
    if (c[n][i]>0 && !u[i] && go(i,sour,sink)) {
      c[n][i]--;
      c[i][n]++;
      return 1;
    }

  return 0;
}

int main () {

  int runs;
  cin>>runs;
  while (runs--) {

    double D;
    cin>>N>>D;

    int P=0;
    vector<int> x(N),y(N),p(N),n(N);
    for (int i=0; i<N; i++) {
      cin>>x[i]>>y[i]>>p[i]>>n[i];
      P+=p[i];
    }

    vector<int> sol;
    
    for (int dest=0; dest<N; dest++) {
      c = vector<vector<int> >(2*N, vector<int>(2*N, 0));

      for (int i=0; i<N; i++) c[2*i][2*i+1] = n[i];
      
      for (int i=0; i<N; i++)
	for (int j=0; j<N; j++)
	  if (i!=j && (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<=D*D)
	    c[2*i+1][2*j] = 9999;

      for (int i=0; i<N; i++)
	if (i!=dest) c[2*dest+1][2*i] = p[i];

      int flow=0;
      while (go(2*dest+1, 2*dest+1, 2*dest)) flow++;

      if (flow == P-p[dest]) sol.push_back(dest);
    }

    if (sol.size()==0)
      cout<<"-1"<<endl;
    else {
      for (int i=0; i<sol.size(); i++) {
	if (i>0) cout<<" ";
	cout<<sol[i];
      }
      cout<<endl;
    }
  }

  return 0;
}
