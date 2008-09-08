/*
  [NWERC'07] Escape from enemy territory
  by: Jaap Eldering
*/

#include <stdio.h>
#include <stdlib.h>

const int infty = 999999;

const int dx[4] = { 1, 0,-1, 0 };
const int dy[4] = { 0, 1, 0,-1 };

#define maxn 10000
#define maxs 1000

int N, X, Y;

int pos[maxn+2][2]; // 0 = init, 1 = rendezvouz, bases
int sep[maxs+1][maxs+1];
int best[maxs+1][maxs+1][2]; // (x,y) -> (minsep, dist)

int min(int a, int b) { if ( a<b ) return a; return b; }

void bfs_fillsep()
{
	int que[(maxs+1)*(maxs+1)][2];
	int first, end;
	int x, y, x1, y1, d;

	for(x=0; x<X; x++)
		for(y=0; y<Y; y++)
			sep[x][y] = infty;

	first = 0;
	for(end=0; end<N; end++) {
		x = que[end][0] = pos[end+2][0];
		y = que[end][1] = pos[end+2][1];
		sep[x][y] = 0;
	}

	while ( first<end ) {
		x = que[first][0];
		y = que[first][1];
		first++;
		for(d=0; d<4; d++) {
			x1 = x+dx[d];
			y1 = y+dy[d];
			if ( x1<0 || x1>=X || y1<0 || y1>=Y ) continue;
			
			if ( sep[x][y]+1<sep[x1][y1] ) {
				sep[x1][y1] = sep[x][y]+1;
				que[end][0] = x1;
				que[end][1] = y1;
				end++;
			}
		}
	}
}

int bfs_minsepdist(int trysep)
{
	int dist[maxs][maxs];
	int que[maxs*maxs][2];
	int first, end;
	int x, y, x1, y1, d;

	for(x=0; x<X; x++)
		for(y=0; y<Y; y++)
			dist[x][y] = infty;

	first = 0;
	end = 1;
	x = que[0][0] = pos[0][0];
	y = que[0][1] = pos[0][1];
	dist[x][y] = 0;
	
	if ( sep[x][y]<trysep ) return infty;

	while ( first<end ) {
		x = que[first][0];
		y = que[first][1];
		first++;
		for(d=0; d<4; d++) {
			x1 = x+dx[d];
			y1 = y+dy[d];
			if ( x1<0 || x1>=X || y1<0 || y1>=Y ) continue;

			if ( sep[x1][y1]>=trysep && dist[x][y]+1<dist[x1][y1] ) {
				dist[x1][y1] = dist[x][y]+1;
				que[end][0] = x1;
				que[end][1] = y1;
				end++;
			}
		}
	}

	return dist[pos[1][0]][pos[1][1]];
}

int main()
{
	int run, nruns;
	int i, j;
	int x, y;
	int sepmin, sepmid, sepmax;
	
	scanf("%d\n",&nruns);

	for(run=1; run<=nruns; run++) {

		// Read and check input
		scanf("%d %d %d\n",&N,&X,&Y);

		if ( N<1 || N>maxn ) return 1;
		if ( X<1 || X>maxs ) return 1;
		if ( Y<1 || Y>maxs ) return 1;

		for(i=0; i<N+2; i++) {
			scanf("%d %d",&pos[i][0],&pos[i][1]);
			if ( pos[i][0]<0 || pos[i][0]>X ||
			     pos[i][1]<0 || pos[i][1]>Y ) return 1;
		}

		for(i=0; i<N+2; i++)
			for(j=0; j<i; j++)
				if ( pos[i][0]==pos[j][0] && pos[i][1]==pos[j][1] ) return 1;

		// calculate distance from bases with breadth first search
		bfs_fillsep();

		// calculate best route with breadth first search and binary
		// search over minimum separation
		sepmin = 0;
		sepmax = 2*maxs;
		while ( sepmin<sepmax ) {
			sepmid = (sepmin+sepmax+1)/2;
			if ( bfs_minsepdist(sepmid)<infty ) {
				sepmin = sepmid;
			} else {
				sepmax = sepmid-1;
			}
		}

		printf("%d %d\n",sepmin,bfs_minsepdist(sepmin));
	}

	return 0;
}
