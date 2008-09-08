/*
  [NWERC'07] ESCAPE
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <queue>

const int dx[4] = { -1,1,0,0 };
const int dy[4] = { 0,0,-1,1 };

int main () {

  int runs;
  cin>>runs;
  while (runs--) {

    int N,X,Y,x1,y1,x2,y2;
    cin>>N>>X>>Y>>x1>>y1>>x2>>y2;
    
    queue<int> q;
    vector<vector<int> > d(X,vector<int>(Y,-1));

    for (int i=0; i<N; i++) {
      int x,y;
      cin>>x>>y;
      d[x][y]=0;
      q.push(x);
      q.push(y);
    }

    while (!q.empty()) {
      int x=q.front(); q.pop();
      int y=q.front(); q.pop();

      for (int i=0; i<4; i++) {
	int nx=x+dx[i], ny=y+dy[i];
	if (nx<0 || nx>=X || ny<0 || ny>=Y) continue;
	if (d[nx][ny]!=-1) continue;

	d[nx][ny]=d[x][y]+1;
	q.push(nx);
	q.push(ny);
      }
    }

    int lo=-1, hi=min(d[x1][y1],d[x2][y2]), sol=-1;
    
    while (lo!=hi) {
      int mid=(lo+hi+1)/2;

      vector<vector<int> > d2(X,vector<int>(Y,-1));

      d2[x1][y1]=0;
      q.push(x1);
      q.push(y1);

      while (!q.empty()) {
	int x=q.front(); q.pop();
	int y=q.front(); q.pop();

	for (int i=0; i<4; i++) {
	  int nx=x+dx[i], ny=y+dy[i];
	  if (nx<0 || nx>=X || ny<0 || ny>=Y) continue;
	  if (d[nx][ny]<mid) continue;
	  if (d2[nx][ny]!=-1) continue;
	  
	  d2[nx][ny]=d2[x][y]+1;
	  q.push(nx);
	  q.push(ny);
	}
      }
      
      if (d2[x2][y2]==-1) hi=mid-1; else lo=mid, sol=d2[x2][y2];
    }

    cout<<lo<<" "<<sol<<endl;
  }
  
  return 0;  
}
