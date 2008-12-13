/* NWERC 2008: Sample solution to "Sculpture"
 * Author: Per Austrin
 *
 * Algorithm: coordinate compression + floodfill
 *            complexity O(n^4), can easily be turned into O(n^3)
 */
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int dx[] = {-1, 0, 0, 1, 0, 0};
const int dy[] = {0, -1, 0, 0, 1, 0};
const int dz[] = {0, 0, -1, 0, 0, 1};

int compress(int n, int *x, int *v) {
  memcpy(v, x, sizeof(int)*n);
  v[n] = -1; 
  sort(v, v+n+1);
  int m = unique(v, v+n+1)-v;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) if (x[i] == v[j]) { x[i] = j; break; }
  return m;
}

int occ[110][110][110];

void solve() {
  int N;
  scanf("%d", &N);
  int X[150], Y[150], Z[150];
  int xv[150], yv[150], zv[150];
  for (int i = 0; i < N; ++i) {
    scanf("%d%d%d%d%d%d", X+2*i, Y+2*i, Z+2*i, X+2*i+1, Y+2*i+1, Z+2*i+1);
    X[2*i+1] += X[2*i]; Y[2*i+1] += Y[2*i]; Z[2*i+1] += Z[2*i];
  }
  int xn = compress(2*N, X, xv);
  int yn = compress(2*N, Y, yv);
  int zn = compress(2*N, Z, zv);
  memset(occ, 0, sizeof(occ));
  
  for (int i = 0; i < N; ++i)
    for (int x = X[2*i]; x < X[2*i+1]; ++x)
      for (int y = Y[2*i]; y < Y[2*i+1]; ++y)
	for (int z = Z[2*i]; z < Z[2*i+1]; ++z)
	  occ[x][y][z] = true;
  vi Q;
  Q.push_back(0);
  occ[0][0][0] = -1;
  while (!Q.empty()) {
    int v = Q.back(); Q.pop_back();
    int x = v & 0xFF, y = (v>>8) & 0xFF, z = (v>>16) & 0xFF;
    for (int d = 0; d < 6; ++d) {
      int nx = x + dx[d], ny = y + dy[d], nz = z + dz[d];
      if (nx >= 0 && ny >= 0 && nz >= 0 && nx < xn && ny < yn && nz < zn &&
	  !occ[nx][ny][nz]) {
	occ[nx][ny][nz] = -1;
	Q.push_back((nz<<16)|(ny<<8)|nx);
      }
    }
  }
  ll vol = 0, area = 0;
  for (int x = 1; x < xn-1; ++x)
    for (int y = 1; y < yn-1; ++y)
      for (int z = 1; z < zn-1; ++z) {
	int sx = xv[x+1]-xv[x], sy = yv[y+1]-yv[y], sz = zv[z+1] - zv[z];
	if (occ[x][y][z] != -1) vol += (ll)sx*sy*sz;
	for (int d = 0; d < 6; ++d)
	  if (occ[x][y][z] != -1 && occ[x+dx[d]][y+dy[d]][z+dz[d]] == -1)
	    area += dx[d] ? sy*sz : dy[d] ? sx*sz : sx*sy;
      }
  printf("%lld %lld\n", area, vol);
}

int main(void) {
  int N;
  for (scanf("%d", &N); N--; solve());
  return 0;
}
