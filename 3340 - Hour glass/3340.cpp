/*
  Memory limit exceeded
 */
#include <deque>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int M, N, T;

typedef int state;

inline state encode(int m, int n, int t){ return m*10000000+n*10000+t; }
inline void decode(state mask, int &m, int &n, int &t){
    t = mask % 10000;
    n = (mask % 10000000) / 10000;
    m = (mask / 10000000);
}

/*
  option = 0 si no se movio ningun reloj, 1 si se movio M, 2 si se movio N, 3 si se movio N,M
 */
void enqueue(state previous, int m, int n, int t, deque<state> &q, map<state, string> &path, int option = 0){
  if (t > T) return;
  state u = encode(m, n, t);
  if (path.count(u) > 0) return;

  char buf[32];
  buf[0] = '\0';
  if (option == 1) sprintf(buf, "%d: %d\n", t, M);
  if (option == 2) sprintf(buf, "%d: %d\n", t, N);
  if (option == 3) sprintf(buf, "%d: %d,%d\n", t, M, N);

  path[u] = path[previous] + string(buf);
  if (option == 0) q.push_front(u);
  else q.push_back(u);
}

void bfs(){
    deque<state> q;
    set<state> visited;
    map<state, string> path;
    char buf[32];
    state initial = encode(M, N, 0);
    sprintf(buf, "0: %d,%d\n", M, N);
    path[initial] = string(buf);

    q.push_front(initial);
    while (q.size()){
      state u = q.front();
      q.pop_front();

      //cout << "popped " << u << endl;

      if (visited.count(u)) continue;

      int m, n, t;
      decode(u, m, n, t);

      if (t > T) continue;

      if (t == T && (m == 0 || n == 0)){
        printf("%s----------\n", path[u].c_str());
        return;
      }

      if (m != 0 && n != 0){
        int z = m < n ? m : n;
        enqueue(u, m-z, n-z, t+z, q, path);
      }else if (m == 0 && n == 0){
        enqueue(u, M, 0, t, q, path, 1);
        enqueue(u, 0, N, t, q, path, 2);
        enqueue(u, M, N, t, q, path, 3);
      }else if (m == 0){
        enqueue(u, M, n, t, q, path, 1);
        enqueue(u, 0, N-n, t, q, path, 2);
        enqueue(u, M, N-n, t, q, path, 3);
        enqueue(u, 0, 0, t+n, q, path);
      }else{
        enqueue(u, m, N, t, q, path, 2);
        enqueue(u, M-m, 0, t, q, path, 1);
        enqueue(u, M-m, N, t, q, path, 3);
        enqueue(u, 0, 0, t+m, q, path);
      }
    }

    printf("Impossible!\n----------\n");
}

int main(){
    while (scanf("%d %d %d", &M, &N, &T) == 3 && (M+N+T)){
      bfs();
    }
    return 0;
}
