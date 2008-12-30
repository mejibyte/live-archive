/*
  Time limit exceeded.

  Correct output but it's too slow.
  (Dijkstra's algorithm using several common queues)
 */
using namespace std;
#include <queue>
#include <cstdio>

const int oo = INT_MAX / 4;
int X, Y;
bool can_jump[1000][1000];
int d[1000][1000];

#define valid(x, y) (0 <= x && x < X && 0 <= y && y < Y && can_jump[x][y])

typedef pair<int, pair<int, int> > state;

const int MAX_EDGE = 8;

int current_queue;
queue<state> q[MAX_EDGE];

void enqueue(int x, int y, int w){
  q[w%MAX_EDGE].push(make_pair(w, make_pair(x, y)));
}

bool dequeue(int &x, int &y, int &w){
  int started_at = current_queue;
  while (q[current_queue].empty()){
    current_queue = (current_queue + 1)%MAX_EDGE;
    if (current_queue == started_at) return false; //no more states to pop
  }
  state &s = q[current_queue].front();
  x = s.second.first, y = s.second.second, w = s.first;
  q[current_queue].pop();
  return true;
}

int dijkstra(int sx, int sy, int ex, int ey){
  for (int i=0; i<MAX_EDGE; ++i) q[i] = queue<state>();

  d[sx][sy] = 0;
  current_queue = 0;
  enqueue(sx, sy, 0);
  for (int x, y, w; dequeue(x, y, w); ){

    if (w > d[x][y]) continue;
    if (x == ex && y == ey) break;

    for (int dx=-2; dx<=2; ++dx){
      for (int dy=-2; dy<=2; ++dy){
        if (dx || dy){ //avoid (0,0)
          int nx = x + dx;
          int ny = y + dy;
          if (!valid(nx, ny)) continue;

          int w_extra = abs(x-nx)+abs(y-ny)+1+2*(abs(x-nx)==2 || abs(y-ny)==2);
          if (w + w_extra < d[nx][ny]){
            d[nx][ny] = w + w_extra;
            enqueue(nx, ny, w + w_extra);
          }
        }
      }
    }
  }

  return d[ex][ey];
}

int main(){
  while (scanf("%d %d", &X, &Y)==2 && X && Y){
    //cleaning
    for (int x=0; x<X; ++x)
      for (int y=0; y<Y; ++y){
        d[x][y] = oo;
        can_jump[x][y] = 1;
      }

    int sx, sy, ex, ey; //start && end coordinates
    scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
    --sx, --sy, --ex, --ey;
    int w;
    for (scanf("%d", &w); w--; ){
      int ax, ay, bx, by;
      scanf("%d %d %d %d", &ax, &ay, &bx, &by);
      --ax, --ay, --bx, --by;
      for (int x=ax; x<=bx; ++x)
        for (int y=ay; y<=by; ++y)
          can_jump[x][y] = false;
    }

    int t = dijkstra(sx, sy, ex, ey);
    if (t < oo) printf("%d\n", t);
    else printf("impossible\n");

  }
  return 0;
}
