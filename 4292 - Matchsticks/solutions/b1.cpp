/*
  [NWERC'08] EQUIVALENCES
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <vector>

int N,M;
vector<int> u,s;
vector<vector<int> > c1,c2;

void dfs1 (int n) {
  if (u[n]) return;
  u[n]=-1;
  for (int i=0; i<c1[n].size(); i++) dfs1(c1[n][i]);
  s.push_back(n);
}

void dfs2 (int n, int mark) {
  if (u[n]!=-1) return;
  u[n]=mark;
  for (int i=0; i<c2[n].size(); i++) dfs2(c2[n][i],mark);
}

int main () {

  int runs;
  cin>>runs;

  while (runs--) {

    cin>>N>>M;
    c1=c2=vector<vector<int> >(N);

    for (int i=0; i<M; i++) {
      int a,b;
      cin>>a>>b;
      a--; b--;
      c1[a].push_back(b);
      c2[b].push_back(a);
    }

    s.clear();
    
    int mark=0;
    u=vector<int>(N,0);
    for (int i=0; i<N; i++) dfs1(i);
    for (int i=N-1; i>=0; i--) if (u[s[i]]==-1) dfs2(s[i], mark++);

    if (mark==1) {
      cout<<0<<endl;
      continue;
    }
    
    vector<int> nin(mark,0), nout(mark,0);

    for (int i=0; i<N; i++) 
      for (int j=0; j<c1[i].size(); j++) if (u[i]!=u[c1[i][j]]) {
	nout[u[i]]++;
	nin[u[c1[i][j]]]++;
      }

    int nin0=0, nout0=0;
    for (int i=0; i<mark; i++) {
      if (nin[i]==0) nin0++;
      if (nout[i]==0) nout0++;
    }

    cout<<max(nin0,nout0)<<endl;
  }
  
  return 0;
}
