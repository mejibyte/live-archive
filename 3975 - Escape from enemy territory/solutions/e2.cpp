/* Sample solution to Escape From Enemy Territory from NWERC 2007
 *
 * Author: Per Austrin
 *
 * Algorithm: 3 x BFS, complexity O(X*Y + N)
 */
#include<queue>
#define BFS(D, Q, C, N) \
    for(q.push((nx<<10)|ny); !q.empty(); q=nq) for(c(); !q.empty(); q.pop()) \
      for (int d = 0, v = q.front(), x = v>>10, y = v&1023; d < 4; ++d) \
	if ((nx=x+dy[d^2]) >= 0 && (ny=y+dy[d]) >= 0 && nx < X && ny < Y && \
	    (C) && D[nx][ny] < 0) D[nx][ny] = (N), (Q).push((nx<<10)|ny);
std::queue<int> q, nq;
int dy[] = {0,0,-1,1}, D[3][1100][1100], T, N, X, Y, x0, y0, x1, y1, nx, ny;
void c() { while (!nq.empty()) nq.pop(); }
int main(void) {
  for (scanf("%d",&T); scanf("%d%d%d%d%d%d%d",&N,&X,&Y,&x0,&y0,&x1,&y1), T--;
      printf("%d %d\n", D[1][x1][y1], D[2][x1][y1])) {
    for ( memset(D, -1, sizeof(D)); N--; )
      scanf("%d%d", &nx, &ny), D[0][nx][ny] = 0, q.push((nx<<10)|ny);
    BFS(D[0], q, 1, D[0][x][y]+1);
    D[1][nx=x0][ny=y0] = D[0][x0][y0]; 
    BFS(D[1], D[1][nx][ny]<D[1][x][y]?nq:q, 1, D[0][nx][ny] <? D[1][x][y]);
    D[2][nx=x0][ny=y0] = 0;
    BFS(D[2], q, D[0][nx][ny]>=D[1][x1][y1], D[2][x][y]+1);
  }
  return 0;
}
