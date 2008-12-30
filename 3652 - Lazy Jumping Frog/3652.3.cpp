/*
  Accepted!

  (Dijkstra's algorithm using several common queues)
*/
using namespace std;
#include <queue>
#include <cstdio>

const int oo = INT_MAX / 4;
int X, Y;
bool can_jump[1000][1000];
int d[1000][1000];
const int energy[5][5] =
  {
    {7, 6, 5, 6, 7},
    {6, 3, 2, 3, 6},
    {5, 2, 0, 2, 5},
    {6, 3, 2, 3, 6},
    {7, 6, 5, 6, 7}
  };

#define valid(x, y) (0 <= x && x < X && 0 <= y && y < Y && can_jump[x][y])

struct state{
  int x, y, w;
  state(){} state(const int &x, const int &y, const int &w) : x(x), y(y), w(w) {}
};

const int MAX_EDGE = 8, MAX_QUEUE_SIZE = 5000;

int current_queue;
state q[MAX_EDGE][MAX_QUEUE_SIZE];
int q_size[MAX_EDGE];

void enqueue(const int &x, const int &y, const int &w){
  int where = w % MAX_EDGE;
  q[where][q_size[where]].x = x;
  q[where][q_size[where]].y = y;
  q[where][q_size[where]].w = w;
  q_size[where]++;
}

bool dequeue(int *x, int *y, int *w){
  int started_at = current_queue;
  while (q_size[current_queue] == 0){
    current_queue++;
    if (current_queue == MAX_EDGE) current_queue = 0;
    if (current_queue == started_at) return false; //no more states to pop
  }
  const state &s = q[current_queue][--q_size[current_queue]];
  *x = s.x, *y = s.y, *w = s.w;
  return true;
}

int dijkstra(const int &sx, const int &sy, const int &ex, const int &ey){
  //clean queues
  for (int i=0; i<MAX_EDGE; ++i)
    q_size[i] = 0;

  d[sx][sy] = 0;
  current_queue = 0;
  enqueue(sx, sy, 0);
  for (int x, y, w; dequeue(&x, &y, &w); ){

    if (w > d[x][y]) continue;
    if (x == ex && y == ey) break;

    //printf("popped (%d, %d, %d)\n", x, y, w);

    for (int dx=-2; dx<=2; ++dx){
      for (int dy=-2; dy<=2; ++dy){
        int nx = x + dx;
        int ny = y + dy;
        if (!valid(nx, ny)) continue;

        const int w_extra = energy[dx+2][dy+2];
        if (w + w_extra < d[nx][ny]){
          d[nx][ny] = w + w_extra;
          enqueue(nx, ny, w + w_extra);
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
