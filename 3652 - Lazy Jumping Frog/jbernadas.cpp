#include "assert.h"
#include "ctype.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "algorithm"
#include "numeric"
#include "functional"
#include "bitset"
#include "vector"
#include "list"
#include "set"
#include "map"
#include "queue"
#include "stack"
#include "string"
#include "sstream"
using namespace std;


typedef long long i64;
#define all(x) (x).begin(), (x).end()

//////////////////////////////////////////////////////////////////////////////////////////

struct node_t {
  int x, y;
};

const int MAX_BOARD = 1000;
const int OBSTACLE = -1;
const int OFFBOARD = -2;
const int FREE = 0;
const int MAXVALS = 10;
const int MAXENTRIES = 2000;
const int kEnergy[5][5] = {
  {7,6,5,6,7},
  {6,3,2,3,6},
  {5,2,0,2,5},
  {6,3,2,3,6},
  {7,6,5,6,7}
};

int board[MAX_BOARD + 4][MAX_BOARD + 4];
int cost[MAX_BOARD + 4][MAX_BOARD + 4];
int R, C;

node_t vals[MAXVALS][MAXENTRIES];
int nvals[MAXVALS], kmin;

int GetNextNode(int* x, int* y) {
  int i, tries = 0;
  kmin = kmin % MAXVALS;
  do {
    while (nvals[kmin] == 0) {
      kmin = (kmin + 1) % MAXVALS;
      if (++tries == MAXVALS)
        return -1;
    }
    i = --nvals[kmin];
    *x = vals[kmin][i].x;
    *y = vals[kmin][i].y;
  } while ((cost[*y][*x] % MAXVALS) != kmin);
  return 0;
}

void Insert(int x, int y, int k) {
  k %= MAXVALS;
  const int i = nvals[k]++;
  vals[k][i].x = x; vals[k][i].y = y;
}

void Dijkstra(int rs, int cs, int rt, int ct) {
  kmin = 2;
  memset(nvals, 0, sizeof(nvals));
  cost[rs][cs] = 0;
  for (int rv = rs, cv = cs; (rv != rt || cv != ct) && board[rv][cv] == FREE;) {
    for (int i = -2; i < 3; ++i) for (int j = -2; j < 3; ++j)
      if (board[rv + i][cv + j] == FREE && cost[rv + i][cv + j] > cost[rv][cv] + kEnergy[i + 2][j + 2]) {
        cost[rv + i][cv + j] = cost[rv][cv] + kEnergy[i + 2][j + 2];
        Insert(cv + j, rv + i, cost[rv + i][cv + j]);
      }
    if (GetNextNode(&cv, &rv) == -1) break;
  }
}

int main(void) {
  for (int i = 0; i < MAX_BOARD + 4; ++i)
    board[0][i] = board[1][i] = board[i][0] = board[i][1] = OFFBOARD;
  for (; scanf("%d %d", &C, &R) == 2 && R > 0;) {
    for (int i = 2; i < C + 4; ++i)
      board[R + 2][i] = board[R + 3][i] = OFFBOARD;
    for (int i = 2; i < R + 4; ++i)
      board[i][C + 2] = board[i][C + 3] = OFFBOARD;
    for (int i = 2; i < R + 2; ++i) for (int j = 2; j < C + 2; ++j)
      board[i][j] = FREE, cost[i][j] = INT_MAX;
    int cs, rs, ct, rt, B;
    scanf("%d %d %d %d %d", &cs, &rs, &ct, &rt, &B);
    for (int k = 0; k < B; ++k) {
      int c1, r1, c2, r2;
      scanf("%d %d %d %d", &c1, &r1, &c2, &r2);
      ++c1, ++c2, ++r1, ++r2;
      for (int i = r1; i <= r2; ++i) for (int j = c1; j <= c2; ++j)
        board[i][j] = OBSTACLE;
    }
    Dijkstra(++rs, ++cs, ++rt, ++ct);
    if (cost[rt][ct] >= INT_MAX) printf("impossible\n");
    else printf("%d\n", cost[rt][ct]);
  }
  return 0;
}
