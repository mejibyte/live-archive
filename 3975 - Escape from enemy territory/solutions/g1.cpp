/*
  [NWERC'07] SUMMITS
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <queue>

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int main () {

  int runs;
  cin>>runs;
  while (runs--) {

    int Y,X,D;
    cin>>Y>>X>>D;
    vector<vector<int> > h(Y,vector<int>(X));
    vector<pair<int,pair<int,int> > > s;
    
    for (int y=0; y<Y; y++)
      for (int x=0; x<X; x++) {
	cin>>h[y][x];
	s.push_back(make_pair(h[y][x],make_pair(y,x)));
      }
    sort(s.begin(),s.end());

    int res=0;
    vector<vector<int> > u(Y,vector<int>(X,-1));
    
    for (int i=Y*X-1; i>=0; i--) {
      int sy=s[i].second.first;
      int sx=s[i].second.second;
      if (u[sy][sx]!=-1) continue;

      int ok=1;
      int pos=0;
      queue<int> q;
      q.push(sy);
      q.push(sx);

      while (!q.empty()) {
	int y=q.front(); q.pop();
	int x=q.front(); q.pop();
	if (u[y][x]!=-1) continue;
	u[y][x]=i;

	if (h[y][x] == h[sy][sx]) pos++;

	for (int d=0; d<4; d++) {
	  int ny=y+dy[d], nx=x+dx[d];
	  if (ny<0 || ny>=Y || nx<0 || nx>=X) continue;
	  if (h[ny][nx] <= h[sy][sx]-D) continue;
	  if (u[ny][nx]>i) ok=0;
	  if (u[ny][nx]==-1) { q.push(ny); q.push(nx); }
	}	
      }

      if (ok) res+=pos;
    }
      
    cout<<res<<endl;
  }

  return 0;
}
