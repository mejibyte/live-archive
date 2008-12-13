/*
  [NWERC'08] CAT VS DOG
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>

int C,D;
vector<vector<int> > c;
vector<int> u,m;

int go (int n) {

  if (u[n]) return 0;
  u[n]=1;

  for (int i=0; i<D; i++)
    if (c[n][i] && (m[i]==-1 || go(m[i]))) {
      m[i]=n;
      return 1;
    }

  return 0;
}

int main () {

  int runs;
  cin>>runs;
  while (runs--) {

    int V;
    cin>>C>>D>>V;
    
    vector<string> c1,c2,d1,d2;
    
    for (int i=0; i<V; i++) {
      string v1,v2;
      cin>>v1>>v2;;
      if (v1[0]=='C') {
	c1.push_back(v1);
	c2.push_back(v2);
      }
      else {
	d1.push_back(v1);
	d2.push_back(v2);
      }
    }

    C=c1.size();
    D=d1.size();
    c=vector<vector<int> >(C, vector<int>(D, 0));

    for (int i=0; i<C; i++)
      for (int j=0; j<D; j++)
	if (c1[i]==d2[j] || c2[i]==d1[j]) c[i][j]=1;

    m=vector<int>(D,-1);

    int sol=V;
    for (int i=0; i<C; i++) {
      u=vector<int>(C,0);
      if (go(i)) sol--;
    }
    
    cout<<sol<<endl;
  }

  return 0;
}
