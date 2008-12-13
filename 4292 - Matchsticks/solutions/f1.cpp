/*
  [NWERC'08] SCULPTURE
  by: Jan Kuipers
*/

using namespace std;

#include <iostream>
#include <queue>
#include <map>
#include <algorithm>

void compress (vector<int> x0, vector<int> dx, vector<int> &i2x, map<int,int> &x2i, int &X) {

  i2x.clear();
  i2x.push_back(INT_MAX);
  i2x.push_back(-INT_MAX);
  
  for (int i=0; i<x0.size(); i++) {
    i2x.push_back(x0[i]);
    i2x.push_back(x0[i]+dx[i]);
  }

  sort(i2x.begin(),i2x.end());
  i2x.erase(unique(i2x.begin(),i2x.end()),i2x.end());
  X=i2x.size();

  for (int i=0; i<X; i++) x2i[i2x[i]] = i;
}

int main () {

  int runs;
  cin>>runs;

  while (runs--) {

    int N;
    cin>>N;
      
    vector<int> x0(N),y0(N),z0(N),dx(N),dy(N),dz(N);
    
    for (int i=0; i<N; i++) 
      cin>>x0[i]>>y0[i]>>z0[i]>>dx[i]>>dy[i]>>dz[i];

    int X,Y,Z;
    vector<int> i2x, i2y, i2z;
    map<int,int> x2i, y2i, z2i;
    
    compress(x0,dx,i2x,x2i,X);
    compress(y0,dy,i2y,y2i,Y);
    compress(z0,dz,i2z,z2i,Z);

    int a[X][Y][Z];

    for (int x=0; x<X; x++)
      for (int y=0; y<Y; y++)
	for (int z=0; z<Z; z++)
	  a[x][y][z] = 2;

    for (int i=0; i<N; i++) {
      int frx=x2i[x0[i]], tox=x2i[x0[i]+dx[i]];
      int fry=y2i[y0[i]], toy=y2i[y0[i]+dy[i]];
      int frz=z2i[z0[i]], toz=z2i[z0[i]+dz[i]];

      for (int x=frx; x<tox; x++)
	for (int y=fry; y<toy; y++)
	  for (int z=frz; z<toz; z++)
	    a[x][y][z] = 1;
    }

    queue<int> q;
    q.push(0);
    q.push(0);
    q.push(0);

    while (!q.empty()) {
      int x=q.front(); q.pop();
      int y=q.front(); q.pop();
      int z=q.front(); q.pop();

      if (x<0 || x>=X || y<0 || y>=Y || z<0 || z>=Z) continue;
      if (a[x][y][z]!=2) continue;
      a[x][y][z]=0;

      for (int dx=-1; dx<=1; dx++)
	for (int dy=-1; dy<=1; dy++)
	  for (int dz=-1; dz<=1; dz++)
	    if (abs(dx)+abs(dy)+abs(dz) == 1) {
	      q.push(x+dx);
	      q.push(y+dy);
	      q.push(z+dz);
	    }
    }

    int A=0, V=0;
    
    for (int x=1; x<X-1; x++)
      for (int y=1; y<Y-1; y++)
	for (int z=1; z<Z-1; z++) {
	  if (a[x][y][z]+a[x-1][y][z] == 1) A += (i2y[y+1]-i2y[y])*(i2z[z+1]-i2z[z]);
	  if (a[x][y][z]+a[x][y-1][z] == 1) A += (i2x[x+1]-i2x[x])*(i2z[z+1]-i2z[z]);
	  if (a[x][y][z]+a[x][y][z-1] == 1) A += (i2x[x+1]-i2x[x])*(i2y[y+1]-i2y[y]);
	  if (a[x][y][z]) V += (i2x[x+1]-i2x[x])*(i2y[y+1]-i2y[y])*(i2z[z+1]-i2z[z]);
	}

    cout<<A<<" "<<V<<endl;
  }
  
  return 0;  
}
